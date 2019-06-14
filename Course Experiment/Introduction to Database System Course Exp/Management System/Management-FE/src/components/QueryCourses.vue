<template>
  <el-main>
    <el-button @click="query" style="margin-bottom: 10px">查询</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column  align="left" prop="CID" label="课程编号"></el-table-column>
      <el-table-column  align="center" prop="CName" label="课程名称"></el-table-column>
      <el-table-column  align="center" prop="CCredit" label="课程学分"></el-table-column>
      <el-table-column  align="right" prop="CTerm" label="开设学期" :formatter="TransType"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryCourses',
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/QueryCourses',
      queryInfo: []
    }
  },
  methods: {
    query () {
      axios.get(this.path + this.api)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    TransType (row, column) {
      return row.CTerm ? '秋季学期' : '春季学期'
    }
  }

}
</script>

<style scoped>

</style>
