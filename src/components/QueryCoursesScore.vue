<template>
    <el-main>
      <el-row>
        <el-button type="primary" @click="query" >刷新</el-button>
      </el-row>
      <el-table :data="queryInfo" style="width: 100%">
        <el-table-column align="left" prop="CID" label="课程编号"></el-table-column>
        <el-table-column align="center" prop="CName" label="课程名称"></el-table-column>
        <el-table-column align="center" prop="SID" label="学生编号"></el-table-column>
        <el-table-column align="center" prop="SName" label="学生姓名"></el-table-column>
        <el-table-column align="center" prop="TotalScore" label="课程总成绩" :formatter="TransType"></el-table-column>
      </el-table>
    </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryCoursesScore',
  props: {
    usrname: ''
  },
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryTotalScores',
      queryInfo: []
    }
  },
  methods: {
    query () {
      axios.post(this.path + this.queryApi, {SID: this.usrname})
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    TransType (row, column) {
      return row.TotalScore === null ? '未录入' : row.TotalScore
    }
  },
  created: function () {
    this.query()
  }
}
</script>

<style scoped>

</style>
