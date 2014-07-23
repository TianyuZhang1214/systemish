# Print the current CPU GHz
for i in `seq 0 15`; do
	freq=`sudo cat /sys/devices/system/cpu/cpu$i/cpufreq/cpuinfo_cur_freq`
	echo "CPU $i: $freq KHz"
done

