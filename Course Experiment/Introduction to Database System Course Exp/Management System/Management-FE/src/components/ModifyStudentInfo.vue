<template>
  <el-main>
    <el-button size="mini" type="primary" @click="dialogFormVisible=true; modifyState = 0; ">插入</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="SID" label="学生编号"></el-table-column>
      <el-table-column align="center" prop="SName" label="学生姓名"></el-table-column>
      <el-table-column align="center" prop="SSex" label="学生性别" :formatter="TransType"></el-table-column>
      <el-table-column align="center" prop="SDept" label="所属院系"></el-table-column>
      <el-table-column align="center" prop="SAdmYear" label="入学年份"></el-table-column>
      <el-table-column align="center" label="操作">
        <template slot-scope="scope">
          <el-button size="mini" type="success" @click="dialogFormVisible=true; modifyState=1; copy(scope.row)">修改</el-button>
          <el-button size="mini" type="danger" @click="deleteStudent(scope.$index, scope.row)">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-dialog title="学生信息" :visible.sync="dialogFormVisible">
      <el-form :model="student">
        <el-form-item label="学生编号:" >
          <el-input v-model="student.SID" :disabled="modifyState>0"></el-input>
        </el-form-item>
        <el-form-item label="学生姓名" >
          <el-input v-model="student.SName"></el-input>
        </el-form-item>
        <el-form-item label="学生性别:">
          <el-radio-group  v-model="student.SSex">
            <el-radio :label="0" >男</el-radio>
            <el-radio :label="1" >女</el-radio>
          </el-radio-group>
        </el-form-item>
        <el-form-item label="所属院系:">
          <el-input v-model="student.SDept"></el-input>
        </el-form-item>
        <el-form-item label="入学年份:">
          <el-date-picker
            v-model="student.SAdmYear"
            placeholder="选择年份"
            value-format="yyyy"
            type="year">
          </el-date-picker>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="primary" @click="modifyState ? updateStudent() : insertStudent()">确 定</el-button>
      </div>
    </el-dialog>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'ModifyStudentInfo',
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryStudents',
      insertApi: '/InsertStudent',
      updateApi: '/UpdateStudent',
      deleteApi: '/DeleteStudent',
      modifyState: 0,
      dialogFormVisible: false,
      queryInfo: [],
      student: {
        SID: '',
        SName: '',
        SSex: 0,
        SDept: '',
        SAdmYear: ''
      }
    }
  },
  methods: {
    queryStudent () {
      axios.get(this.path + this.queryApi)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    insertStudent () {
      axios.post(this.path + this.insertApi, this.student)
        .then(res => {
          if (res.data['State']) {
            this.queryStudent()
            this.$message({message: '插入成功', type: 'success'})
          } else {
            this.$message.error('插入失败')
          }
        })
    },
    updateStudent () {
      this.dialogFormVisible = false
      axios.post(this.path + this.updateApi, this.student)
        .then(res => {
          if (res.data['State']) {
            this.queryStudent()
            this.$message({message: '修改成功', type: 'success'})
          } else {
            this.$message.error('修改失败')
          }
        })
    },
    deleteStudent (index, row) {
      this.$confirm('确认删除该行数据？')
        .then(_ => {
          axios.post(this.path + this.deleteApi, { SID: row.SID })
            .then(res => {
              if (res.data['State']) {
                this.queryStudent()
                this.$message({message: '删除成功', type: 'success'})
              } else {
                this.$message.error('删除失败')
              }
            })
        })
    },
    copy (row) {
      this.student.SID = row.SID
      this.student.SName = row.SName
      this.student.SSex = row.SSex
      this.student.SDept = row.SDept
      this.student.SAdmYear = row.SAdmYear.toString()
      console.log(this.student)
    },
    TransType (row, column) {
      return row.SSex ? '男' : '女'
    }
  },
  created () {
    this.queryStudent()
  }
}
</script>

<style scoped>

</style>
