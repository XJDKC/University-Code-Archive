<template>
  <el-main>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="Username" label="账号"></el-table-column>
      <el-table-column align="center" prop="Password" label="密码"></el-table-column>
      <el-table-column align="center" prop="Usertype" label="账号类型" :formatter="TransType"></el-table-column>
      <el-table-column align="center" label="操作">
        <template slot-scope="scope">
          <el-button size="mini" type="success" @click="dialogFormVisible=true; usr=scope.row">修改</el-button>
          <el-button size="mini" type="danger" @click="deleteUser(scope.$index, scope.row)">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-dialog title="修改账号信息" :visible.sync="dialogFormVisible">
      <el-form :model="usr">
        <el-form-item label="账号:" >
          <el-input v-model="usr.Username" :disabled="true"></el-input>
        </el-form-item>
        <el-form-item label="密码" >
          <el-input v-model="usr.Password"></el-input>
        </el-form-item>
        <el-form-item label="用户类型:">
          <el-radio-group  v-model="usr.Usertype">
            <el-radio :label="0">管理员</el-radio>
            <el-radio :label="1">教师</el-radio>
            <el-radio :label="2">学生</el-radio>
          </el-radio-group>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="primary" @click="updateUser">确 定</el-button>
      </div>
    </el-dialog>

  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'UpdateDeleteUser',
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryUsers',
      updateApi: '/UpdateUser',
      deleteApi: '/DeleteUser',
      dialogFormVisible: false,
      queryInfo: [],
      usr: {
        Username: '',
        Password: '',
        Usertype: 0
      }
    }
  },
  methods: {
    query () {
      axios.get(this.path + this.queryApi)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    updateUser () {
      this.dialogFormVisible = false
      axios.post(this.path + this.updateApi, this.usr)
        .then(res => {
          if (res.data['State']) {
            this.query()
            this.$message({message: '修改成功', type: 'success'})
          } else {
            this.$message.error('修改失败')
          }
        })
    },
    deleteUser (index, row) {
      this.$confirm('确认删除该行数据？')
        .then(_ => {
          axios.post(this.path + this.deleteApi, { Username: row.Username })
            .then(res => {
              if (res.data['State']) {
                this.query()
                this.$message({message: '删除成功', type: 'success'})
              } else {
                this.$message.error('删除失败')
              }
            })
        })
    },
    TransType (row, column) {
      switch (row.Usertype) {
        case 0: return '管理员'
        case 1: return '教师'
        case 2: return '学生'
      }
    }
  },
  created () {
    this.query()
  }
}
</script>

<style scoped>

</style>
