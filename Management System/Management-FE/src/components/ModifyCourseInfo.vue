<template>
  <el-main>
    <el-button size="mini" type="primary" @click="dialogFormVisible=true; modifyState = 0; ">插入</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="CID" label="课程编号"></el-table-column>
      <el-table-column align="center" prop="CName" label="课程姓名"></el-table-column>
      <el-table-column align="center" prop="CCredit" label="课程学分"></el-table-column>
      <el-table-column align="center" prop="CTerm" label="开设学期" :formatter="TransType"></el-table-column>
      <el-table-column align="center" label="操作">
        <template slot-scope="scope">
          <el-button size="mini" type="success" @click="dialogFormVisible=true; modifyState=1; copy(scope.row)">修改</el-button>
          <el-button size="mini" type="danger" @click="deleteCourse(scope.$index, scope.row)">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-dialog title="课程信息" :visible.sync="dialogFormVisible">
      <el-form :model="course">
        <el-form-item label="课程编号:" >
          <el-input v-model.number="course.CID" :disabled="modifyState>0"></el-input>
        </el-form-item>
        <el-form-item label="课程姓名" >
          <el-input v-model="course.CName"></el-input>
        </el-form-item>
        <el-form-item label="课程学分:">
          <el-input v-model="course.CCredit"></el-input>
        </el-form-item>
        <el-form-item label="开设学期:">
          <el-radio-group  v-model="course.CTerm">
            <el-radio :label="0">春季学期</el-radio>
            <el-radio :label="1">秋季学期</el-radio>
          </el-radio-group>
        </el-form-item>
      </el-form>
      <div slot="footer" class="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="primary" @click="modifyState ? updateCourse() : insertCourse()">确 定</el-button>
      </div>
    </el-dialog>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'ModifyCourseInfo',
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryCourses',
      insertApi: '/InsertCourse',
      updateApi: '/UpdateCourse',
      deleteApi: '/DeleteCourse',
      modifyState: 0,
      dialogFormVisible: false,
      queryInfo: [],
      course: {
        CID: 0,
        CName: '',
        CCredit: 0.0,
        CTerm: Boolean
      }
    }
  },
  methods: {
    queryCourse () {
      axios.get(this.path + this.queryApi)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    insertCourse () {
      this.course.CCredit = parseFloat(this.course.CCredit)
      axios.post(this.path + this.insertApi, this.course)
        .then(res => {
          if (res.data['State']) {
            this.queryCourse()
            this.$message({message: '插入成功', type: 'success'})
          } else {
            this.$message.error('插入失败')
          }
        })
    },
    updateCourse () {
      this.dialogFormVisible = false
      this.course.CCredit = parseFloat(this.course.CCredit)
      axios.post(this.path + this.updateApi, this.course)
        .then(res => {
          if (res.data['State']) {
            this.queryCourse()
            this.$message({message: '修改成功', type: 'success'})
          } else {
            this.$message.error('修改失败')
          }
        })
    },
    deleteCourse (index, row) {
      this.$confirm('确认删除该行数据？')
        .then(_ => {
          axios.post(this.path + this.deleteApi, { CID: row.CID })
            .then(res => {
              if (res.data['State']) {
                this.queryCourse()
                this.$message({message: '删除成功', type: 'success'})
              } else {
                this.$message.error('删除失败')
              }
            })
        })
    },
    copy (row) {
      this.course.CID = row.CID
      this.course.CName = row.CName
      this.course.CCredit = row.CCredit
      this.course.CTerm = row.CTerm
      console.log(this.course)
    },
    TransType (row, column) {
      return row.CTerm ? '秋季学期' : '春季学期'
    }
  },
  created () {
    this.queryCourse()
  }
}
</script>

<style scoped>

</style>
