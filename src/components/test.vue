<template>
  <el-main>
    <el-button @click="onButtonClicked"></el-button>
    <el-table :data="tableData" style="width: 100%">
      <el-table-column prop="date" label="日期" width="140">
      </el-table-column>
      <el-table-column prop="name" label="姓名" width="120">
      </el-table-column>
      <el-table-column prop="address" label="地址">
      </el-table-column>
    </el-table>
  </el-main>
</template>

<script>
export default {
  name: 'test',
  data () {
    return {
      tableData: []
    }
  },
  methods: {
    onButtonClicked () {
      this.tableData.push({
        date: '2019-6-1',
        name: 'XJDKC',
        address: '武汉'
      })
    }
  }
}
</script>

<style scoped>
  .el-main{
    background-color: whitesmoke;
  }
</style>
