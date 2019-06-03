<template>
  <el-main>
    <el-input v-model="ClassID"></el-input>
    <el-button @click="query" style="margin-bottom: 10px">查询</el-button>
    <el-button @click="dialogFormVisible = true" style="margin-bottom: 10px">修改</el-button>
    <el-table :data="queryInfo" style="width: 100%">
      <el-table-column align="left" prop="TaskID" label="任务编号"></el-table-column>
      <el-table-column align="center" prop="Weight" label="权重"></el-table-column>
    </el-table>
    <el-dialog title="教师信息" :visible.sync="dialogFormVisible">
      <el-form>
        <el-form-item v-for="(item, index) in weightList" v-bind:key="item" :label="item">Task {{ index+1 }}
        </el-form-item>
      </el-form>
      <el-input v-model="newWeight"></el-input>
      <div slot="footer" class="dialog-footer">
        <el-button @click="dialogFormVisible = false">取 消</el-button>
        <el-button @click="weightList.push(newWeight)">新 增</el-button>
        <el-button type="primary" @click="update">确 定</el-button>
      </div>
    </el-dialog>
  </el-main>
</template>

<script>
import axios from 'axios'

export default {
  name: 'ModifyTaskWeight',
  data () {
    return {
      path: 'http://localhost:5000',
      queryApi: '/QueryTaskByTeacher',
      upateApi: '/ModifyTaskWeight',
      Usrname: 'T201610282',
      dialogFormVisible: false,
      newWeight: 0,
      ClassID: 0,
      weightList: [],
      queryInfo: []
    }
  },
  methods: {
    query () {
      this.ClassID = parseInt(this.ClassID)
      axios.post(this.path + this.queryApi, {TID: this.Usrname, ClassID: this.ClassID})
        .then(res => { console.log(res.data); this.queryInfo = res.data })
    },
    update () {
      this.classID = parseInt(this.ClassID)
      axios.post(this.path + this.upateApi, {TID: this.Usrname, ClassID: this.ClassID, Weights: this.weightList})
        .then(this.$message({message: '修改成功', type: 'success'}))
      this.dialogFormVisible = false
    }
  }
}
</script>

<style scoped>

</style>
