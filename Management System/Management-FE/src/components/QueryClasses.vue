<template>
  <el-main>
    <el-button @click="query" style="margin-bottom: 10px">查询</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="ClassID" label="课堂编号"></el-table-column>
      <el-table-column align="center" prop="CID" label="课程编号"></el-table-column>
      <el-table-column align="center" prop="CName" label="课堂名称"></el-table-column>
      <el-table-column align="center" prop="TID" label="教师编号"></el-table-column>
      <el-table-column align="right" prop="TName" label="教师名称"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryClasses',
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/QueryClasses',
      queryInfo: []
    }
  },
  methods: {
    query () {
      axios.get(this.path + this.api)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    TransType (row, column) {
      if (parseInt(row.CTerm.substring(4, 2)) <= 6) {
        return row.CTerm.substring(0, 4) + '年春季学期'
      } else {
        return row.CTerm.substring(0, 4) + '年秋季学期'
      }
    }
  }

}
</script>

<style scoped>

</style>
