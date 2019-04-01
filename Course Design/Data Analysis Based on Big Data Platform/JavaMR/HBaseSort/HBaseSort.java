import java.io.IOException;
import java.util.List;
import java.util.ArrayList;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.hbase.*;
import org.apache.hadoop.hbase.client.*;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.hbase.mapreduce.TableMapper;
import org.apache.hadoop.hbase.mapreduce.TableReducer;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.hbase.mapreduce.TableOutputFormat;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.mapreduce.SimpleTotalOrderPartitioner;

public class HBaseSort {

	public static String sourceTable = "";
	public static String targetTable = "";

	public static void main(String[] args) throws Exception {

		sourceTable = args[0];
		targetTable = args[1];

		Configuration config = HBaseConfiguration.create();
		//config.set("hbase.hstore.blockingStoreFiles", "10");
		//config.set("hbase.hstore.blockingWaitTime", "90000");
		//config.set("hbase.hregion.memstore.flush.size","268435456");
		//config.set("hbase.hstore.flusher.count", "64");
		//config.set("hbase.ipc.server.max.callqueue,size", "1073741824");
		//config.set("hbase.regionserver.executor.openregion.threads","8");
		//config.set("hbase.regionserver.executor.closeregion.threads","8");
		//config.set("hbase.regionserver.thread.compaction.large", "1");
		//config.set("hbase.regionserver.thread.compaction.small", "1");
		Job job = new Job(config, "HBase Sorting");
		job.setJarByClass(HBaseSort.class); 

		job.setNumReduceTasks(1);

		Scan scan = new Scan();
		scan.setCaching(500);
		scan.setCacheBlocks(false);

		TableMapReduceUtil.initTableMapperJob(sourceTable, scan, HBaseSortMapper.class, Text.class, Text.class, job);
		TableMapReduceUtil.initTableReducerJob(targetTable, HBaseSortReducer.class, job);


		boolean b = job.waitForCompletion(true);
		if (!b) {
			throw new IOException("error with job!");
		}
	}

	public static class HBaseSortMapper extends TableMapper<Text, Text>  {

		public void map(ImmutableBytesWritable row, Result value, Context context) throws IOException, InterruptedException {
			// this example is just copying the data from the source table...
			String val = new String(Bytes.toString(value.getValue(Bytes.toBytes("info"), Bytes.toBytes("score"))));
			String line = new String(Bytes.toString(value.getValue(Bytes.toBytes("info"), Bytes.toBytes("name"))) + ","
			                         + Bytes.toString(value.getValue(Bytes.toBytes("info"), Bytes.toBytes("score"))));
			Text key = new Text(), rowInfo = new Text();
			key.set(String.format("%5s", val));
			rowInfo.set(line);
			context.write(key, rowInfo);
		}
	}

	public static class HBaseSortReducer extends TableReducer<Text, Text, ImmutableBytesWritable>  {
		private int no = 0;
		public void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {

			while (values.iterator().hasNext()) {
				Put put = new Put(Bytes.toBytes(String.format("%09d", no)));
				no = no + 1;
				String[] columns = values.iterator().next().toString().split(",");

				put.addColumn(Bytes.toBytes("info"), Bytes.toBytes("name"), columns[0].getBytes());
				put.addColumn(Bytes.toBytes("info"), Bytes.toBytes("score"), columns[1].getBytes());

				context.write(null, put);
			}
		}
	}
}
