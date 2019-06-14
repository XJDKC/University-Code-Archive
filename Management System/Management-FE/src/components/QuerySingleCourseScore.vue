<template>
  <el-main>
    <el-row style="margin-bottom: 10px">
      <a>所选课程</a>
      <el-select v-model.number="classID" placeholder="请选择" filterable style="margin-right: 10px; margin-left: 10px">
        <el-option v-for="item in classList" :key="item.ClassID" :label="item.ClassID" :value="item.ClassID">
          <span style="float: left">{{ item.ClassID }}</span>
          <span style="float: right; color: #8492a6; font-size: 13px">{{ item.CName }}</span>
        </el-option>
      </el-select>
      <el-button type="primary" @click="query" >查询</el-button>
    </el-row>
    <el-table :data="queryInfo" style="width: 100%" :summary-method="getTotalScore" show-summary>
      <el-table-column align="left" prop="TaskID" label="任务编号"></el-table-column>
      <el-table-column align="center" prop="TaskName" label="任务名称"></el-table-column>
      <el-table-column align="center" prop="Weight" label="任务比重"></el-table-column>
      <el-table-column align="center" prop="SID" label="学生编号"></el-table-column>
      <el-table-column align="center" prop="SName" label="学生名称"></el-table-column>
      <el-table-column align="center" prop="Score" label="学生分数" :formatter="TransType"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QuerySingleCourseScore',
  props: {
    usrname: ''
  },
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryScores',
      queryClassesApi: '/QueryClasses',
      classList: [],
      queryInfo: [],
      classID: 0
    }
  },
  methods: {
    query () {
      if (this.classID !== 0) {
        axios.post(this.path + this.queryApi, {SID: this.usrname, ClassID: this.classID})
          .then(res => { console.log(res.data); this.queryInfo = res.data })
      } else {
        this.$message.error('请选择一个课堂')
      }
    },
    queryClasses () {
      axios.post(this.path + this.queryClassesApi, { SID: this.usrname })
        .then(res => { console.log(res.data); this.classList = res.data })
    },
    getTotalScore (param) {
      const { columns, data } = param
      const sums = []
      console.log(data)
      columns.forEach((column, index) => {
        if (index === 0) {
          sums[index] = '总成绩'
          return
        }
        const values = data.map(item => Number(item[column.property]))
        sums[index] = 0
        console.log(values)
        if (!values.every(value => isNaN(value))) {
          for (var i = 0; i < data.length; ++i) {
            if (index === 5) {
              sums[index] += data[i].Weight * values[i] / 100.0
            } else {
              sums[index] += values[i]
            }
          }
        } else {
          sums[index] = 'N/A'
        }
      })

      return sums
    },
    TransType (row, column) {
      console.log(row.Score)
      return row.Score === null ? '未录入' : row.Score
    }
  },
  created: function () {
    this.queryClasses()
  }
}
</script>

<style scoped>

</style>
