<template>
  <el-main>
    <div>
      <el-button @click="query" type="primary" style="margin-bottom: 10px">刷新</el-button>
    </div>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="ClassID" label="课堂编号"></el-table-column>
      <el-table-column align="center" prop="CID" label="课程编号"></el-table-column>
      <el-table-column align="center" prop="CName" label="课程名称"></el-table-column>
      <el-table-column align="center" prop="SID" label="学生编号"></el-table-column>
      <el-table-column align="center" prop="SName" label="学生姓名"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'
export default {
  name: 'QueryClassByStudent',
  props: {
    usrname: ''
  },
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/QueryClasses',
      queryInfo: []
    }
  },
  methods: {
    query () {
      console.log(this.username)
      axios.post(this.path + this.api, {SID: this.usrname})
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    }
  },
  created: function () {
    this.query()
  }
}
</script>

<style scoped>

</style>
