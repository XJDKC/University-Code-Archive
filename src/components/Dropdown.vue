<template>
  <div style="height: 50px; margin-top: 5px">
    <el-dropdown style="height: 50px; vertical-align: middle">
      <span style="margin-top: 25px; font-size: 15px">XJDKC</span>
      <i class="el-icon-arrow-down" style="margin-top: 15px; font-size: 15px;"></i>
      <el-dropdown-menu slot="dropdown">
        <el-dropdown-item @click="onHelpClicked">帮助</el-dropdown-item>
        <el-dropdown-item @click="onQuitClicked">退出登录</el-dropdown-item>
      </el-dropdown-menu>
    </el-dropdown>
  </div>
</template>

<script>
export default {
  name: 'Dropdown',
  props: ['Usrname'],
  methods: {
    onHelpClicked () {
      this.$emit('help')
    },
    onQuitClicked () {
      this.$emit('quit')
    }
  }

}
</script>

<style scoped>

</style>
