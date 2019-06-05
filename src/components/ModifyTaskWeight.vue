<template>
  <el-main>
    <el-row style="margin-bottom: 10px">
      <el-select v-model.number="classID" placeholder="请选择" filterable style="margin-right: 10px">
        <el-option v-for="item in classList" :key="item.ClassID" :label="item.ClassID" :value="item.ClassID">
          <span style="float: left">{{ item.ClassID }}</span>
          <span style="float: right; color: #8492a6; font-size: 13px">{{ item.CName }}</span>
        </el-option>
      </el-select>
      <el-button type="primary" @click="query" >查询</el-button>
      <el-button type="danger"  @click="judge">修改</el-button>
      <el-button type="success" @click="refresh">刷新</el-button>
    </el-row>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="TaskID" label="任务编号"></el-table-column>
      <el-table-column align="center" prop="TaskName" label="任务名称"></el-table-column>
      <el-table-column align="center" prop="Weight" label="任务权重"></el-table-column>
      <el-table-column align="center" prop="Type" label="任务类型" :formatter="TransType"></el-table-column>
    </el-table>
    <el-dialog title="任务信息" :visible.sync="dialogFormVisible" center style="width: 100%">
      <el-table :data="weightList" style="width: 100%">
        <el-table-column align="left" type="index" label="序号"></el-table-column>
        <el-table-column align="center" property="TaskName" label="任务名称"></el-table-column>
        <el-table-column align="center" property="Weight" label="任务权重"></el-table-column>
        <el-table-column align="center" property="Type" label="任务类型" :formatter="TransType"></el-table-column>
        <el-table-column align="center" label="操作">
          <template slot-scope="scope">
            <el-button size="mini" type="danger" @click="deleteTask(scope.$index, scope.row)">删除</el-button>
          </template>
        </el-table-column>
      </el-table>
      <div slot="footer">
        <el-button type="info"    @click="dialogFormVisible = false">取 消</el-button>
        <el-button type="success" @click="innerVisible=true">新 增</el-button>
        <el-button type="primary" @click="update">确 定</el-button>
      </div>

      <el-dialog title="新任务" :visible.sync="innerVisible" append-to-body>
        <el-form  :model="newTask">
          <el-form-item label="名称">
            <el-input v-model="newTask.TaskName" width="25px"></el-input>
          </el-form-item>
          <el-form-item label="权重">
            <el-input v-model.number="newTask.Weight" width="25px"></el-input>
          </el-form-item>
          <el-switch v-model="newTask.Type" active-text="测试" inactive-text="作业" active-value="1" inactive-value="0"></el-switch>
        </el-form>
        <div slot="footer">
          <el-button type="info"    @click="innerVisible=false">取 消</el-button>
          <el-button type="primary" @click="addToList">确 定</el-button>
        </div>
      </el-dialog>
    </el-dialog>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'ModifyTaskWeight',
  props: {
    usrname: ''
  },
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryTasks',
      upateApi: '/ModifyTasks',
      queryClassesApi: '/QueryClasses',
      dialogFormVisible: false,
      innerVisible: false,
      classList: [],
      queryInfo: [],
      classID: 0,
      weightList: [],
      newTask: {
        TaskID: 0,
        ClassID: '',
        TaskName: '',
        Weight: '',
        Type: 0
      }
    }
  },
  methods: {
    refresh () {
      this.query()
      this.queryClasses()
    },
    query () {
      axios.post(this.path + this.queryApi, {TID: this.usrname, ClassID: this.classID})
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    queryClasses () {
      axios.post(this.path + this.queryClassesApi, {TID: this.usrname})
        .then(res => { console.log(res.data); this.classList = res.data })
    },
    update () {
      var sum = 0
      console.log(this.weightList)
      for (var i = 0; i < this.weightList.length; i++) {
        sum = sum + this.weightList[i].Weight
        console.log(sum)
      }
      if (sum === 100) {
        axios.post(this.path + this.upateApi, {TID: this.usrname, ClassID: this.classID, Weights: this.weightList})
          .then(res => {
            if (res.data['State']) {
              this.$message({message: '修改成功', type: 'success'})
            } else {
              this.$message.error('修改失败')
            }
          })
      } else {
        this.$message.error('权重和应为100')
      }
      this.dialogFormVisible = false
    },
    TransType (row, columb) {
      return row.Type ? '测试' : '作业'
    },
    judge () {
      if (this.classID === 0) {
        this.$message.error('请先选择一个课堂')
      } else {
        axios.post(this.path + this.queryApi, {TID: this.usrname, ClassID: this.classID})
          .then(res => {
            this.weightList = res.data
            this.dialogFormVisible = true
          })
      }
    },
    deleteTask (index, row) {
      this.weightList.splice(index, 1)
    },
    addToList () {
      var temp = {
        TaskID: 0,
        ClassID: '',
        TaskName: '',
        Weight: '',
        Type: 0
      }
      this.newTask.TaskID = this.weightList.length + 1
      this.newTask.ClassID = this.classID
      Object.assign(temp, this.newTask)
      temp.Type = parseInt(temp.Type)
      this.weightList.push(temp)
      this.innerVisible = false
    }
  },
  created: function () {
    this.queryClasses()
  }
}
</script>

<style scoped>

</style>
