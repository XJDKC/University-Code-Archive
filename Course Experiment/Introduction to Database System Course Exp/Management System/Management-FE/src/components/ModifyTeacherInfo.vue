<template>
  <el-main>
    <el-button size="mini" type="primary" @click="dialogFormVisible=true; modifyState = 0; ">插入</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="TID" label="教师编号"></el-table-column>
      <el-table-column align="center" prop="TName" label="教师姓名"></el-table-column>
      <el-table-column align="center" prop="TSex" label="教师性别" :formatter="TransType"></el-table-column>
      <el-table-column align="center" prop="TDept" label="所属院系"></el-table-column>
      <el-table-column align="center" label="操作">
        <template slot-scope="scope">
          <el-button size="mini" type="success" @click="dialogFormVisible=true; modifyState=1; teacher=Object.assign({},scope.row)">修改</el-button>
          <el-button size="mini" type="danger" @click="deleteTeacher(scope.$index, scope.row)">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-dialog title="教师信息" :visible.sync="dialogFormVisible">
      <el-form :model="teacher">
        <el-form-item label="教师编号:" >
          <el-input v-model="teacher.TID" :disabled="modifyState>0"></el-input>
        </el-form-item>
        <el-form-item label="教师姓名" >
          <el-input v-model="teacher.TName"></el-input>
        </el-form-item>
        <el-form-item label="教师性别:">
          <el-radio-group  v-model="teacher.TSex">
            <el-radio :label="0" >男</el-radio>
            <el-radio :label="1" >女</el-radio>
          </el-radio-group>
        </el-form-item>
        <el-form-item label="所属院系:">
          <el-input v-model="teacher.TDept"></el-input>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="primary" @click="state ? updateTeacher() : insertTeacher()">确 定</el-button>
      </div>
    </el-dialog>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'ModifyTeacherInfo',
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryTeachers',
      insertApi: '/InsertTeacher',
      updateApi: '/UpdateTeacher',
      deleteApi: '/DeleteTeacher',
      modifyState: 0,
      dialogFormVisible: false,
      queryInfo: [],
      teacher: {
        TID: '',
        TName: '',
        TSex: 0,
        TDept: ''
      }
    }
  },
  methods: {
    queryTeacher () {
      axios.get(this.path + this.queryApi)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    insertTeacher () {
      axios.post(this.path + this.insertApi, this.teacher)
        .then(res => {
          if (res.data['State']) {
            this.queryTeacher()
            this.$message({message: '插入成功', type: 'success'})
          } else {
            this.$message.error('插入失败')
          }
        })
    },
    updateTeacher () {
      this.dialogFormVisible = false
      axios.post(this.path + this.updateApi, this.teacher)
        .then(res => {
          if (res.data['State']) {
            this.queryTeacher()
            this.$message({message: '修改成功', type: 'success'})
          } else {
            this.$message.error('修改失败')
          }
        })
    },
    deleteTeacher (index, row) {
      this.$confirm('确认删除该行数据？')
        .then(_ => {
          axios.post(this.path + this.deleteApi, { TID: row.TID })
            .then(res => {
              if (res.data['State']) {
                this.queryTeacher()
                this.$message({message: '删除成功', type: 'success'})
              } else {
                this.$message.error('删除失败')
              }
            })
        })
    },
    TransType (row, column) {
      return row.TSex ? '男' : '女'
    }
  },
  created () {
    this.queryTeacher()
  }
}
</script>

<style scoped>

</style>
