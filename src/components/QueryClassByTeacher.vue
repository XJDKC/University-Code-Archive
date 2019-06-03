<template>
  <el-main>
    <el-button @click="query" style="margin-bottom: 10px">查询</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="ClassID" label="课堂编号"></el-table-column>
      <el-table-column align="center" prop="CID" label="课程编号"></el-table-column>
      <el-table-column align="center" prop="CName" label="课堂名称"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryClassByTeacher',
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/QueryClassByTeacher',
      Usrname: 'T201610282',
      queryInfo: []
    }
  },
  methods: {
    query () {
      axios.post(this.path + this.api, {TID: this.Usrname})
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    }
  }
}
</script>

<style scoped>

</style>
