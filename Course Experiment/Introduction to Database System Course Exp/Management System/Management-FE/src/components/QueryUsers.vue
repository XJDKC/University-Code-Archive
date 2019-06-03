<template>
  <el-main>
    <el-radio-group v-model="type" style="margin-right: 10px">
      <el-radio :label="-1">所有</el-radio>
      <el-radio :label="0">管理员</el-radio>
      <el-radio :label="1">教师</el-radio>
      <el-radio :label="2">学生</el-radio>
    </el-radio-group>
    <el-button @click="query">查询</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column  align="left" prop="Username" label="账号"></el-table-column>
      <el-table-column  align="center" prop="Password" label="密码"></el-table-column>
      <el-table-column  align="right" prop="Usertype" label="账号类型" :formatter="TransType"></el-table-column>
    </el-table>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'QueryUsers',
  data () {
    return {
      type: -1,
      path: 'http://localhost:5000',
      api: '/QueryUsers',
      queryInfo: []
    }
  },
  methods: {
    query () {
      if (this.type !== -1) {
        axios.post(this.path + this.api, {'usrtype': this.type})
          .then(res => { console.log(res.data); this.queryInfo = res.data })
      } else {
        axios.get(this.path + this.api)
          .then(res => { console.log(res.data); this.queryInfo = res.data })
      }
    },
    TransType (row, column) {
      switch (row.Usertype) {
        case 0: return '管理员'
        case 1: return '教师'
        case 2: return '学生'
      }
    }
  }
}
</script>

<style scoped>

</style>
