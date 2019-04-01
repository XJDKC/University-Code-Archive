#!/bin/env bash
hadoop fs -rm -r /move/

hadoop jar /opt/hadoop/hadoop-2.8.5/share/hadoop/tools/lib/hadoop-streaming-2.8.5.jar \
        -input $1 \
        -output /move \
        -file $2 \
        -mapper $2 \
        -jobconf mapred.job.name="move_from_hdfs_to_hbase" \
        -cmdenv "table_name=$3" \
        -cmdenv "num=$4" \
