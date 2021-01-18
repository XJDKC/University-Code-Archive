<template>
  <el-main>
    <el-row style="margin-bottom: 10px">
      <a>课堂: </a>
      <el-select v-model.number="classID" placeholder="请选择" filterable style="margin-right: 10px" @change="queryTasks">
        <el-option v-for="item in classList" :key="item.ClassID" :label="item.ClassID" :value="item.ClassID">
          <span style="float: left">{{ item.ClassID }}</span>
          <span style="float: right; color: #8492a6; font-size: 13px">{{ item.CName }}</span>
        </el-option>
      </el-select>
      <a>任务: </a>
      <el-select v-model.number="taskID" placeholder="请选择" filterable style="margin-right: 10px">
        <el-option v-for="item in taskList" :key="item.TaskID" :label="item.TaskID" :value="item.TaskID">
          <span style="float: left">{{ item.TaskID }}</span>
          <span style="float: right; color: #8492a6; font-size: 13px">{{ item.TaskName }}</span>
        </el-option>
      </el-select>
      <el-button type="primary" @click="query" >查询</el-button>
      <el-button type="success" @click="refresh">刷新</el-button>
    </el-row>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="TaskID" label="任务编号"></el-table-column>
      <el-table-column align="center" prop="TaskName" label="任务名称"></el-table-column>
      <el-table-column align="center" prop="Weight" label="任务权重"></el-table-column>
      <el-table-column align="center" prop="SID" label="学生编号"></el-table-column>
      <el-table-column align="center" prop="SName" label="学生名称"></el-table-column>
      <el-table-column align="center" prop="Score" label="学生分数" :formatter="TransType"></el-table-column>
      <el-table-column align="center" label="操作">
        <template slot-scope="scope">
          <el-button size="mini" type="danger" @click="updateScore(scope.$index, scope.row)">修改</el-button>
        </template>
      </el-table-column>
    </el-table>
    <el-dialog title="成绩信息" :visible.sync="dialogFormVisible" center style="width: 100%">
        <el-form >
          <el-form-item label="成绩">
            <el-input v-model="newScore" width="25px"></el-input>
          </el-form-item>
        </el-form>
        <div slot="footer">
          <el-button type="info"    @click="dialogFormVisible=false">取 消</el-button>
          <el-button type="primary" @click="mode?update():insertScore()">确 定</el-button>
        </div>
    </el-dialog>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'InputScore',
  props: {
    usrname: ''
  },
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryScores',
      upateApi: '/UpdateScore',
      insertApi: '/InsertScore',
      queryClassesApi: '/QueryClasses',
      queryTasksApi: '/QueryTasks',
      dialogFormVisible: false,
      classList: [],
      taskList: [],
      queryInfo: [],
      classID: 0,
      taskID: 0,
      SID: '',
      newScore: 0,
      mode: 0
    }
  },
  methods: {
    refresh () {
      this.query()
      this.queryClasses()
    },
    query () {
      axios.post(this.path + this.queryApi, {TID: this.usrname, TaskID: this.taskID})
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    queryClasses () {
      axios.post(this.path + this.queryClassesApi, {TID: this.usrname})
        .then(res => { console.log(res.data); this.classList = res.data })
    },
    queryTasks () {
      axios.post(this.path + this.queryTasksApi, {TID: this.usrname, ClassID: this.classID})
        .then(res => { console.log(res.data); this.taskList = res.data })
    },
    insertScore () {
      this.newScore = parseFloat(this.newScore)
      axios.post(this.path + this.insertApi, {TID: this.usrname, SID: this.SID, TaskID: this.taskID, Score: this.newScore})
        .then(res => {
          if (res.data['State']) {
            this.refresh()
            this.$message({message: '录入成功', type: 'success'})
          } else {
            this.$message.error('录入失败')
          }
        })
      this.dialogFormVisible = false
    },
    update () {
      this.newScore = parseFloat(this.newScore)
      axios.post(this.path + this.upateApi, {TID: this.usrname, SID: this.SID, TaskID: this.taskID, Score: this.newScore})
        .then(res => {
          if (res.data['State']) {
            this.refresh()
            this.$message({message: '修改成功', type: 'success'})
          } else {
            console.log(res['State'])
            this.$message.error('修改失败')
          }
        })
      this.dialogFormVisible = false
    },
    updateScore (index, row) {
      this.SID = row.SID
      console.log(row)
      if (row.Score !== null) {
        this.mode = 1
        this.newScore = row.Score
      } else {
        this.mode = 0
      }
      this.dialogFormVisible = true
    },
    TransType (row, column) {
      console.log(row.Score)
      return row.Score === null ? '未录入' : row.Score
    }
  },
  created: function () {
    this.queryClasses()
  }
}
</script>

<style scoped>

</style>
