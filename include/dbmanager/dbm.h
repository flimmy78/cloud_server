#pragma once
#ifndef __DBM_H__
#define __DBM_H__

#include <osa/osa.h>
#include "dbm_definitions.h"
#include "dbm_utils.h"
#include "dbm_entities.h"


#define DBM_IS_ENTITY_TYPE_VALID(type)      (((type) >= DBM_ENTITY_TYPE_FIRST) && ((type) <= DBM_ENTITY_TYPE_LAST))


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    typedef enum DBM_EntityType {
        DBM_ENTITY_TYPE_NONE                      = 0,
        DBM_ENTITY_TYPE_HOUSE                     = 1,
        DBM_ENTITY_TYPE_EXT_HOUSE                 = 2,
        DBM_ENTITY_TYPE_PERSON                    = 3,
        DBM_ENTITY_TYPE_FLOWING_PERSON            = 4,
        DBM_ENTITY_TYPE_DEVICE                    = 5,
        DBM_ENTITY_TYPE_CARD                      = 6,
        DBM_ENTITY_TYPE_SAMCARD                   = 7,
        DBM_ENTITY_TYPE_CARD_PERMISSION           = 8, 
        DBM_ENTITY_TYPE_CARD_OWNING               = 9,
        DBM_ENTITY_TYPE_USER_HOUSE                = 10,
        DBM_ENTITY_TYPE_ACCESS_RECORD             = 11,
        DBM_ENTITY_TYPE_DEVICE_ALARM              = 12,
        DBM_ENTITY_TYPE_DEVICE_STATUS             = 13,
        DBM_ENTITY_TYPE_COUNT                     = 14,
        DBM_ENTITY_TYPE_FIRST                     = DBM_ENTITY_TYPE_HOUSE, 
        DBM_ENTITY_TYPE_LAST                      = DBM_ENTITY_TYPE_DEVICE_STATUS, 
    } DBM_EntityType;
    

    typedef enum DBM_DataSync {
        DBM_DATA_SYNC_UNSYNCED = 0,
        DBM_DATA_SYNC_SYNCED,
    } DBM_DataSync;
      

    typedef int (*DBM_EntityFilter)(const DBM_EntityType entityType, const void *pEntity);

    #pragma pack(push, 1)
    typedef struct DBM_EntityOptions {
        DBM_EntityType                 entityType;           /* [in] which type of entity do you want to get */
        DBM_EntityFilter               filter;               /* [in] returns 0: do not use this entity; returns non-0: use this entity. Can be used to implement complex filters */
        Char                          *pConditions;          /* [in] the conditions after SQL `WHERE` keyword */
        Uint32                        *pCount;               /* [in][out] the caller fills the count of entities to get; the callee fills the actual count of entities got */
        Uint32                         offset;               /* [in] entities count offset (0 based), relative to the first got entity */
        void                          *pEntities;            /* [out] memory to store the returned entities; the memory shall be allocated by the caller */
        
        /*  
           Example:  Get at most 50 persons that are not synced:
           int ret;          
           DBM_EntityOptions options;           
           OSA_clear(&options);
           Uint32 count = 50;
           
           options.entityType = DBM_ENTITY_TYPE_PERSON;
           options.filter = NULL;
           options.pConditions = "sync = 1";
           options.pCount = &count;
           options.offset = 0;
           options.pBuffer = malloc(sizeof(person) * (*options.pCount));
           ret = DBM_getEntity(handle, &options);
         */
    } DBM_EntityOptions;
    #pragma pack(pop)
        

    /** @brief Initialize this module.    
     *  @param pConnectionString [in]: Connection string is sth. like "User ID = papillon; Password = Hello; Server = localhost; Initial Catalog = SAC"
     *  @param pHandle [out]: the handle to be used in other callings.
     *  @return standard OSA status codes.
     */
    int DBM_init(const Char *pConnectionString, DBM_Handle *pHandle);


    /** @brief De-initialize this module (release any allocated resources)
    *  @param handle [in]: the handle inited by `DBM_init()`
    *  @return standard OSA status codes.
    */
    int DBM_deinit(DBM_Handle handle);
        

    /** @brief Get the size (in bytes) of one entity type.
    *  @param entityType [in]: the entity type you want to get its size.
    *  @return entity size in bytes.
    */
    size_t DBM_getEntitySize(const DBM_EntityType entityType);


    /** @brief Get entities count that matches the specified conditions.
    *  @param handle [in]: the handle inited by `DBM_init()`
    *  @param pOptions [in]: the caller shall fill these fields: entityType, pCount;
    *                        these fields are conditional: filter, pConditions;
    *                        these fields can be ignored: offset, pEntities.
    *   NOTE:                the entities count is returned via the `pCount` field.
    *  @return standard OSA status codes.
    */
    int DBM_getEntitiesCount(DBM_Handle handle, DBM_EntityOptions *pOptions);
       

    /** @brief Get entities that matches the specified conditions.
    *  @param handle [in]: the handle inited by `DBM_init()`
    *  @param pOptions [in]: the caller shall fill these fields: entityType, pCount, offset, pEntities;
    *                        these fields are conditional: filter, pConditions;
    *   NOTE:                expected entities count is specified via the `pCount` field when calling this function;
    *                        when this function returns, actual `pCount` field is filled with actual count (<= specified count).
    *  @return standard OSA status codes.
    */
    int DBM_getEntities(DBM_Handle handle, DBM_EntityOptions *pOptions);


    /** @brief Get one entity that is not synced.
    *  @param handle [in]: the handle inited by `DBM_init()`
    *  @param entityType [in]: the entity type you want to get.
    *  @param pEntity [out]: returned entity.
    *  @param pAssociation: currently please specify NULL.
    *  @return standard OSA status codes. If no unsynced entity of the specified type, it returns `OSA_STATUS_ENODATA`.
    */
    int DBM_getUnsyncedEntity(DBM_Handle handle, const DBM_EntityType entityType, void *pEntity, void *pAssociation);


    /** @brief Update specific fields of entities that match the specified conditions.
    *  @param handle [in]: the handle inited by `DBM_init()`
    *  @param pFieldValues[in]: fields and their values in standard SQL syntax, e.g., "field1 = value1, field2 = value2"
    *  @param pOptions [in]: the caller shall fill these fields: entityType;
    *                        these fields are conditional: pCount, filter, pConditions;
    *                        these fields can be ignored: offset, pEntities.
    *   NOTE:                if the `pCount` field is not NULL, it will be filled as the count of rows updated after this function returns.
    *  @return standard OSA status codes.
    */
    int DBM_updateEntities(DBM_Handle handle, const Char *pFieldValues, DBM_EntityOptions *pOptions);


    /** @brief Overwrite all fields of entities that match the specified conditions.
    *          The caller is responsible to ensure that all fields are valid.
    *  @param handle [in]: the handle inited by `DBM_init()`
    *  @param pOptions [in]: the caller shall fill these fields: entityType, pCount, pEntities;
    *                        these fields are conditional: filter, pConditions;
    *                        these fields can be ignored: offset.
    *   NOTE:                pCount shall alwasys be 1, and pEntities shall contain one entity.
    *                        After this function returns, `pCount` will be filled as actual rows count that was/were overwritten.
    *  @return standard OSA status codes.
    */
    int DBM_overwriteEntities(DBM_Handle handle, DBM_EntityOptions *pOptions);


    /** @brief Insert one entity to database.
    *          Note: all fields are assumed to be valid.
    *  @param handle [in]: the handle inited by `DBM_init()`
    *  @param entityType [in]: the entity type you want to insert.
    *  @param pEntity [in]: the entity itself.
    *                       After successful calling, it is updated to reflect the actual value inserted into database, 
    *                       since some fields will be overwritten by this module.
    *  @param pAssociation: currently please specify NULL.
    *  @return standard OSA status codes.
    */
    int DBM_insertEntity(DBM_Handle handle, const DBM_EntityType entityType, void *pEntity, void *pAssociation);


    /** @brief Insert one entity to database.
    *          Note: silimar to `DBM_insertEntity()` but some fields may be incomplete.
    *  @return standard OSA status codes.
    */
    int DBM_insertEntityFromVendor(DBM_Handle handle, const DBM_EntityType entityType, void *pEntity);
    

    /** @brief Print all fields of en entity.
    *  @param entityType [in]: the entity type you want to print.
    *  @param pEntity [in]: the entity itself.
    *  @return standard OSA status codes.
    */
    int DBM_printEntity(const DBM_EntityType entityType, const void *pEntity);


    /** @brief Delete entities that match the specified conditions.
    *  @param handle [in]: the handle inited by `DBM_init()`    
    *  @param pOptions [in]: the caller shall fill these fields: entityType;
    *                        these fields are conditional: filter, pConditions, pCount;
    *                        these fields can be ignored: offset, pEntities.
    *   NOTE:                if the `pCount` field is not NULL, it will be filled as the count of rows deleted after this function returns.
    *  @return standard OSA status codes.
    */
    int DBM_deleteEntity(DBM_Handle handle, DBM_EntityOptions *pOptions);

#ifdef __cplusplus
}
#endif // __cplusplus



#endif  /* __DBM_H__ */
