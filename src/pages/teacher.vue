<template>
  <el-container style="height: 100%">
    <el-menu @select="changeMenuList" class="el-menu-vertical-demo" text-color="#fff" active-text-color="#409eff" background-color="#304156" :collapse="isCollapse">
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
      <Header :menuList="menuList" :usrname="usrname" v-on:collapseMenu="collapseMenu" v-on:quit="quit"></Header>
      <QueryClassByTeacher  v-if="showMenuNo === '1-1'"></QueryClassByTeacher>
      <ModifyTaskWeight     v-if="showMenuNo === '1-2'"></ModifyTaskWeight>
      <el-footer></el-footer>
    </el-container>
  </el-container>
</template>

<script>
import Header from '@/components/Header'
import test from '@/components/test'
import QueryClassByTeacher from '../components/QueryClassByTeacher'
import ModifyTaskWeight from '../components/ModifyTaskWeight'

export default {
  name: 'teacher',
  components: {ModifyTaskWeight, QueryClassByTeacher, Header, test},
  data () {
    return {
      menuName: [
        { submenu: '课堂信息管理', icon: 'el-icon-location', childs: ['课堂信息查询', '课堂信息修改'] },
        { submenu: '成绩管理', icon: 'el-icon-menu', childs: ['成绩录入', '成绩查询'] }
      ],
      usrname: '',
      isCollapse: true,
      showMenuNo: '1-1',
      menuList: ['Teacher']
    }
  },
  methods: {
    collapseMenu (data) {
      this.isCollapse = data
    },
    quit () {
      this.$router.push({name: 'login'})
    },
    changeMenuList (key, keyPath) {
      this.showMenuNo = key
      var temp = this.menuName
      var keys = key.split('-')
      this.menuList = ['Teacher']
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
  },
  created: function () {
    this.usrname = this.$route.params.Usrname
  }
}
</script>

<style scoped>
  .el-aside {
    background-color: #304156;
  }
  .el-menu{
    color: #fff;
    height: 100%;
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
