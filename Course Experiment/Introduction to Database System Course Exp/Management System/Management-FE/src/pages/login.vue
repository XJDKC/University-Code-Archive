<template>
  <div class="login-body">
    <div class="login-box">
      <el-row>
        <el-input placeholder="人员编号/学号(Username)" v-model="usrname" prefix-icon="el-icon-user">
        </el-input>
      </el-row>

      <el-row>
        <el-input placeholder="请输入密码(Password)" v-model="password" prefix-icon="el-icon-lock" show-password>
        </el-input>
      </el-row>

      <el-row>
        <el-button id="login" v-on:click="check" style="width:100%" type="primary">登录</el-button>
      </el-row>
    </div>

  </div>
</template>

<script>
import axios from 'axios'
import router from '../router'

export default {
  name: 'login',
  data () {
    return {
      usrname: '',
      password: ''
    }
  },

  methods: {
    check () {
      if (this.username === '' || this.password === '') {
        this.$alert('用户名或密码为空', '', {
          confirmButtonText: '确认'
        })
      } else {
        const path = 'http://localhost:5000/loginCheck'
        axios.post(path, {'usrname': this.usrname, 'password': this.password})
          .then(res => {
            this.$alert(res.data.Success, '', {
              confirmButtonText: '确认'
            })
            if (res.data.Success) {
              this.$alert('登陆成功', '', {
                confirmButtonText: '确认'
              })
              var paras = {
                Usrname: res.data.Usrname
              }
              switch (res.data.Usrtype) {
                case 0: router.push({name: 'manager', params: paras}); console.log(0); break
                case 1: router.push({name: 'teacher', params: paras}); console.log(1); break
                case 2: router.push({name: 'student', params: paras}); console.log(2); break
              }
            } else {
              this.$alert('登录失败', '', {
                confirmButtonText: '确认'
              })
            }
          })
          .catch(error => {
            console.log(error)
            this.$alert('登录失败', '', {
              confirmButtonText: '确认'
            })
          })
      }
    }
  }
}
</script>

<style scoped>
  .login-body{
    height: 100%;
    background-image: url("../assets/login.png");
    background-size:cover;
  }
  .login-box{
    margin: 0 auto;
    #border: 1px solid black;
    height: 90%;
    display: flex;
    flex-direction: column;
    justify-content: center;
    resize: vertical;
    overflow: auto;
  }
  .login-footer{
    color: white;
    hieght: 10%;
    text-align: right;
  }
  .el-row {
    margin: 0 auto;
    margin-top: 10px;
    margin-bottom: 10px;
    width: 250px;
    text-align: center;
    #border: 1px solid black;
  }
  .el-col {
    align: center;
  }
  .el-input{
    color: #ffffff;
    background-color: transparent;
  }
</style>
