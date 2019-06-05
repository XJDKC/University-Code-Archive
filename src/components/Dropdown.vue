<template>
  <div style="height: 50px; margin-top: 5px">
    <el-dropdown style="height: 50px; vertical-align: middle" @command="onDropdownClicked">
      <span style="margin-top: 25px; font-size: 15px" v-bind:key="usrname">{{ usrname }}</span>
      <i class="el-icon-arrow-down" style="margin-top: 15px; font-size: 15px;"></i>
      <el-dropdown-menu slot="dropdown">
        <el-dropdown-item command="help">帮助</el-dropdown-item>
        <el-dropdown-item command="quit">退出登录</el-dropdown-item>
      </el-dropdown-menu>
    </el-dropdown>
  </div>
</template>

<script>
export default {
  name: 'Dropdown',
  props: {
    usrname: ''
  },
  methods: {
    onDropdownClicked (command) {
      if (command === 'help') {
        this.$alert('<div>Powered by <a href="https://github.com/XJDKC" style="text-decoration: underline">XJDKC</a></div>'
          , '帮助', {dangerouslyUseHTMLString: true, center: true})
      } else if (command === 'quit') {
        this.$confirm('确认退出？')
          .then(() => {
            console.log(1)
            this.$emit('quit')
          })
      }
    }
  }
}
</script>

<style scoped>

</style>
