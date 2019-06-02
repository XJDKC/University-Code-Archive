<template>
  <el-container style="height: 100%">
    <el-menu
      @select="changeMenuList"
      class="el-menu-vertical-demo"
      text-color="#fff"
      background-color="#304156"
      active-text-color="#409eff"
      :collapse="isCollapse"
    >
      <el-submenu v-for="(first, i) in menuName" :key="i" :index="`${i+1}`">
        <template slot="title">
          <i :class="first.icon"></i>
          <span>{{ first.submenu }}</span>
        </template>
        <el-menu-item v-for="(second, j) in first.childs" :key="i-j" :index="`${i+1}-${j+1}`">
          {{ second }}
        </el-menu-item>
      </el-submenu>
    </el-menu>
    <el-container>
      <Header :newList="menuList" v-on:collapseMenu="collapseMenu" v-on:help="help" v-on:quit="quit"></Header>
      <test v-if="showMenuNo === '1-1'"></test>
      <el-footer></el-footer>
    </el-container>
  </el-container>
</template>

<script>
// import '@/styles/index.scss'
import Header from '@/components/Header'
import test from '@/components/test'

export default {
  name: 'student',
  components: {Header, test},
  data () {
    return {
      menuName: [
        { submenu: '导航1', icon: 'el-icon-location', childs: ['选项1', '选项2'] },
        { submenu: '导航2', icon: 'el-icon-menu', childs: ['选项3', '选项4'] },
        { submenu: '导航3', icon: 'el-icon-location', childs: ['选项5', '选项6'] }
      ],
      menuList: [ 'Student' ],
      isCollapse: false,
      showMenuNo: '0'
    }
  },
  methods: {
    collapseMenu (data) {
      this.isCollapse = data
    },
    help () {
      this.$alert('Powered by XJDKC', '帮助', {confirmButtonText: '确认'})
    },
    quit () {
      this.$alert('确认退出？', '提示', {confirmButtonText: '确认'})
    },
    changeMenuList (key, keyPath) {
      this.showMenuNo = key
      var temp = this.menuName
      var keys = key.split('-')
      this.menuList = ['Student']
      for (var i = 0; i < keys.length; i++) {
        keys[i] = parseInt(keys[i])
        if (i < keys.length - 1) {
          this.menuList.push(temp[keys[i] - 1].submenu)
          temp = temp[keys[i] - 1].childs
        } else {
          this.menuList.push(temp[keys[i] - 1])
        }
      }
    }
  }
}
</script>

<style>
  .el-aside {
    background-color: #304156;
  }
  .el-menu{
    color: #fff;
    overflow-x: hidden;
    overflow-y: auto;
    background-color: #304156;
  }
  .el-submenu {
    background-color: #304156; /* #304156 */
  }
  .el-submenu:hover{
    background-color: #304156!important;
  }
  .el-menu-item {
    background-color: #1F2D3D!important;
  }
  .el-menu-item:hover{
    background-color: #001528!important;
  }
  .el-menu-vertical-demo:not(.el-menu--collapse) {
    width: 200px;
    min-height: 400px;
  }
</style>
