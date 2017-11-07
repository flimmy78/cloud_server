#!/bin/bash

export LD_LIBRARY_PATH="/usr/local/lib/sac"

base=`pwd`
app="server"

is_server_run() {
	cnt=`pidof server | wc -l`
	if [ "$cnt" == "0" ]; then
		return "0"
	fi
	return "1"
}


do_start_demo() {
	while [ 1 ]; do
		${base}/${app} > /dev/null
		sleep 1
	done
}

do_start() {
	is_server_run
	ret=$?
	if [ "$ret" != "0" ]; then
		echo "server has startted!"
		return
	fi

	do_start_demo &
}

do_stop() {
	is_server_run
	ret=$?
	if [ "$ret" == "0" ]; then
		echo "server does't start!"
		return
	fi

	echo "stop server"

	pid=`ps aux | grep server.sh | grep start | xargs | cut -d " " -f 2`
	kill -9 $pid
	kill -9 `pidof server`
}



case $1 in
"start")
	do_start
	;;
"stop")
	do_stop
	;;
*)
	echo "not supportted cmd"
	;;
esac

