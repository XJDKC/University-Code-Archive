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
      <QueryCoursesScore      :usrname="usrname" v-if="showMenuNo === '1-1'"></QueryCoursesScore>
      <QuerySingleCourseScore :usrname="usrname" v-if="showMenuNo === '1-2'"></QuerySingleCourseScore>
      <QueryClassByStudent    :usrname="usrname" v-if="showMenuNo === '2-1'"></QueryClassByStudent>
      <el-footer></el-footer>
    </el-container>
  </el-container>
</template>

<script>
// import '@/styles/index.scss'
import Header from '@/components/Header'
import QueryCoursesScore from '@/components/QueryCoursesScore'
import QuerySingleCourseScore from '@/components/QuerySingleCourseScore'
import QueryClassByStudent from '@/components/QueryClassByStudent'

export default {
  name: 'student',
  components: {QueryClassByStudent, QuerySingleCourseScore, QueryCoursesScore, Header},
  data () {
    return {
      menuName: [
        { submenu: '成绩查询', icon: 'el-icon-location', childs: ['总成绩查询', '单科成绩查询'] },
        { submenu: '课堂查询', icon: 'el-icon-menu', childs: ['查询所选课堂'] }
      ],
      usrname: '',
      showMenuNo: '0',
      isCollapse: true,
      menuList: [ 'Student' ]
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
  },
  created: function () {
    this.usrname = this.$route.params.Usrname
  }
}
</script>

<style>
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
