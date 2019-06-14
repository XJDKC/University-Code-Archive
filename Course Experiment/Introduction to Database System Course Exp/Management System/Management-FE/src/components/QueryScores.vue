<template>
  <el-main>
    <el-row style="margin-bottom: 10px">
      <el-select v-model.number="classID" placeholder="请选择" filterable style="margin-right: 10px">
        <el-option v-for="item in classList" :key="item.ClassID" :label="item.ClassID" :value="item.ClassID">
          <span style="float: left">{{ item.ClassID }}</span>
          <span style="float: right; color: #8492a6; font-size: 13px">{{ item.CName }}</span>
        </el-option>
      </el-select>
      <el-button type="primary" @click="query" >查询</el-button>
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
  name: 'QueryScores',
  props: {
    usrname: ''
  },
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryTotalScores',
      queryClassesApi: '/QueryClasses',
      classList: [],
      queryInfo: [],
      classID: 0
    }
  },
  methods: {
    query () {
      axios.post(this.path + this.queryApi, {TID: this.usrname, ClassID: this.classID})
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    queryClasses () {
      axios.post(this.path + this.queryClassesApi, { TID: this.usrname })
        .then(res => { console.log(res.data); this.classList = res.data })
    },
    TransType (row, column) {
      console.log(row.Score)
      return row.TotalScore === null ? '未录入' : row.TotalScore
    }
  },
  created: function () {
    this.queryClasses()
  }
}
</script>

<style scoped>

</style>
