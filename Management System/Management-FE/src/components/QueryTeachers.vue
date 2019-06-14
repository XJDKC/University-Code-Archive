<template>
  <el-main>
    <el-button @click="query" style="margin-bottom: 10px">查询</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="TID" label="教师编号"></el-table-column>
      <el-table-column align="center" prop="TName" label="教师姓名"></el-table-column>
      <el-table-column align="center" prop="TSex" label="教师性别" :formatter="TransType"></el-table-column>
      <el-table-column align="right" prop="TDept" label="所属院系"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryTeachers',
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/QueryTeachers',
      queryInfo: []
    }
  },
  methods: {
    query () {
      axios.get(this.path + this.api)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    TransType (row, column) {
      switch (row.TSex) {
        case 0: return '男'
        case 1: return '女'
      }
    }
  }

}
</script>

<style scoped>

</style>
