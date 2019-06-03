<template>
  <el-main>
    <el-button @click="query" style="margin-bottom: 10px">查询</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column  align="left" prop="CID" label="课程编号"></el-table-column>
      <el-table-column  align="center" prop="CName" label="课程名称"></el-table-column>
      <el-table-column  align="center" prop="CCredit" label="课程分数"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryTotalGrade',
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/QueryTotalGrade',
      queryInfo: []
    }
  },
  methods: {
    query () {
      axios.post(this.path + this.api, { })
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    }
  }

}
</script>

<style scoped>

</style>
