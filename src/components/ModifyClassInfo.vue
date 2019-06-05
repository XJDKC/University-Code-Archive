<template>
  <el-main>
    <el-button size="mini" type="primary" @click="dialogFormVisible=true; modifyState = 0; ">插入</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="ClassID" label="课堂编号"></el-table-column>
      <el-table-column align="center" prop="CID" label="课程编号"></el-table-column>
      <el-table-column align="center" prop="CName" label="课堂名称"></el-table-column>
      <el-table-column align="center" prop="TID" label="教师编号"></el-table-column>
      <el-table-column align="center" prop="TName" label="教师名称"></el-table-column>
      <el-table-column align="center" label="操作">
        <template slot-scope="scope">
          <el-button size="mini" type="success" @click="dialogFormVisible=true; modifyState=1; copy(scope.row)">修改</el-button>
          <el-button size="mini" type="danger" @click="deleteClass(scope.$index, scope.row)">删除</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-dialog title="课堂信息" :visible.sync="dialogFormVisible" style="padding: -1px">
      <el-form :model="classes">
        <el-form-item label="课堂编号:" >
          <el-input v-model.number="classes.ClassID" :disabled="modifyState"></el-input>
        </el-form-item>
        <el-form-item label="课程编号" >
          <el-input v-model.number="classes.CID"></el-input>
        </el-form-item>
        <el-form-item label="课堂名称" >
          <el-input v-model="classes.CName" disabled="true"></el-input>
        </el-form-item>
        <el-form-item label="教师编号:">
          <el-input v-model="classes.TID"></el-input>
        </el-form-item>
        <el-form-item label="教师名称">
          <el-input v-model="classes.TName" disabled="true"></el-input>
        </el-form-item>
      </el-form>
      <div slot="footer" classes="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="primary" @click="modifyState ? updateClass() : insertClass()">确 定</el-button>
      </div>
    </el-dialog>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'ModifyClassInfo',
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryClasses',
      insertApi: '/InsertClass',
      updateApi: '/UpdateClass',
      deleteApi: '/DeleteClass',
      modifyState: 0,
      dialogFormVisible: false,
      queryInfo: [],
      classes: {
        ClassID: 0,
        CID: 0,
        CName: '',
        TID: '',
        TName: ''
      }
    }
  },
  methods: {
    queryClass () {
      axios.get(this.path + this.queryApi)
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    insertClass () {
      console.log(this.classes)
      axios.post(this.path + this.insertApi, this.classes)
        .then(res => {
          if (res.data['State']) {
            this.queryClass()
            this.$message({message: '插入成功', type: 'success'})
          } else {
            this.$message.error('插入失败')
          }
        })
    },
    updateClass () {
      this.dialogFormVisible = false
      axios.post(this.path + this.updateApi, this.classes)
        .then(res => {
          if (res.data['State']) {
            this.queryClass()
            this.$message({message: '修改成功', type: 'success'})
          } else {
            this.$message.error('修改失败')
          }
        })
    },
    deleteClass (index, row) {
      this.$confirm('确认删除该行数据？')
        .then(_ => {
          axios.post(this.path + this.deleteApi, { ClassID: row.ClassID })
            .then(res => {
              if (res.data['State']) {
                this.queryClass()
                this.$message({message: '删除成功', type: 'success'})
              } else {
                this.$message.error('删除失败')
              }
            })
        })
    },
    copy (row) {
      this.classes.ClassID = row.ClassID
      this.classes.CID = parseInt(row.CID)
      this.classes.CName = row.CName
      this.classes.TID = row.TID
      this.classes.TName = row.TName
    }
  },
  created () {
    this.queryClass()
  }
}
</script>

<style scoped>

</style>
