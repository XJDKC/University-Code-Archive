<template>
  <el-main>
    <div>
      <p>请输入新用户信息</p>
    </div>
    <el-form ref="form" :model="usr" label-width="80px">
      <el-form-item label="账号:">
        <el-input v-model="usr.Username" placeholder="新用户用户名"></el-input>
      </el-form-item>
      <el-form-item label="密码:">
        <el-input v-model="usr.Password" placeholder="新用户密码"></el-input>
      </el-form-item>
      <el-form-item label="用户类型:">
        <el-radio-group  v-model="usr.Usertype">
          <el-radio :label="0" >管理员</el-radio>
          <el-radio :label="1">教师</el-radio>
          <el-radio :label="2" >学生</el-radio>
        </el-radio-group>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="insert">插入新用户</el-button>
      </el-form-item>
    </el-form>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'InsertUser',
  data () {
    return {
      path: 'http://localhost:5000',
      api: '/InsertUser',
      usr: {
        Username: '',
        Password: '',
        Usertype: 0
      }
    }
  },
  methods: {
    insert () {
      axios.post(this.path + this.api, this.usr)
        .then(res => {
          if (res.data['State']) {
            this.$message({message: '插入成功', type: 'success'})
          } else {
            this.$message.error('插入失败')
          }
        })
    }
  }
}
</script>

<style scoped>

</style>
