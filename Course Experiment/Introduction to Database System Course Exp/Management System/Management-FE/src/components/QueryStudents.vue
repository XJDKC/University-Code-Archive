<template>
  <el-main>
    <el-button @click="query" style="margin-bottom: 10px">查询</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column  align="left" prop="SID" label="学生编号"></el-table-column>
      <el-table-column  align="center" prop="SName" label="学生姓名"></el-table-column>
      <el-table-column  align="center" prop="SSex" label="学生性别" :formatter="TransType"></el-table-column>
      <el-table-column  align="center" prop="SDept" label="所属院系"></el-table-column>
      <el-table-column  align="right" prop="SAdmYear" label="入学年份"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryStudents',
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/QueryStudents',
      queryInfo: []
    }
  },
  methods: {
    query () {
      axios.get(this.path + this.api)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    TransType (row, column) {
      switch (row.SSex) {
        case 0: return '男'
        case 1: return '女'
      }
    }
  }

}
</script>

<style scoped>

</style>
