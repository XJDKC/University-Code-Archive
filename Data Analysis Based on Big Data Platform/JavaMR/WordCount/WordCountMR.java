import java.io.IOException;
 
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
 
 
public class WordCountMR {

    public static void main(String[] args) throws Exception {
        // 指定hdfs相关的参数
        Configuration conf = new Configuration();
         
//      conf.set("mapreduce.framework.name", "yarn");
//      conf.set("yarn.resourcemanager.hostname", "jz-xrl");
         
        Job job = Job.getInstance(conf);
         
        // 设置jar包所在路径
        job.setJarByClass(WordCountMR.class);
         
        // 指定mapper类和reducer类
        job.setMapperClass(WordCountMapper.class);
        job.setReducerClass(WordCountReducer.class);
         
        // 指定maptask的输出类型
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(IntWritable.class);
         
        // 指定reducetask的输出类型
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);
         
//      Path inputPath = new Path("d:/wordcount/input");
//      Path outputPath = new Path("d:/wordcount/output");
         
        // 指定该mapreduce程序数据的输入和输出路径
        Path inputPath = new Path("/input/input.txt");
        Path outputPath = new Path("/Java_Out");
        FileSystem fs = FileSystem.get(conf);
        if(fs.exists(outputPath)){
            fs.delete(outputPath, true);
        }
        FileInputFormat.setInputPaths(job, inputPath);
        FileOutputFormat.setOutputPath(job, outputPath);
         
//      job.submit();
        // 最后提交任务
        boolean waitForCompletion = job.waitForCompletion(true);
        System.exit(waitForCompletion?0:1);
    }
   
    static class WordCountMapper extends Mapper<LongWritable, Text, Text, IntWritable>{
        @Override
        protected void map(LongWritable key, Text value,Context context)
                throws IOException, InterruptedException {
             
            String[] words = value.toString().split(" ");
            for(String word: words){
                context.write(new Text(word), new IntWritable(1));
            }
        }
    }
     
    static class WordCountReducer extends Reducer<Text, IntWritable, Text, IntWritable>{
        @Override
        protected void reduce(Text key, Iterable<IntWritable> values, Context context)
                throws IOException, InterruptedException {
             
            int sum = 0;
            for(IntWritable v: values){
                sum += v.get();
            }
            context.write(key, new IntWritable(sum));
        }
    }
}
