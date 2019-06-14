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
      <QueryUsers         v-if="showMenuNo === '1-1'"></QueryUsers>
      <QueryTeachers      v-if="showMenuNo === '1-2'"></QueryTeachers>
      <QueryStudents      v-if="showMenuNo === '1-3'"></QueryStudents>
      <QueryCourses       v-if="showMenuNo === '1-4'"></QueryCourses>
      <QueryClasses       v-if="showMenuNo === '1-5'"></QueryClasses>
      <InsertUser         v-if="showMenuNo === '2-1'"></InsertUser>
      <UpdateDeleteUser   v-if="showMenuNo === '2-2'"></UpdateDeleteUser>
      <ModifyTeacherInfo  v-if="showMenuNo === '3-1'"></ModifyTeacherInfo>
      <ModifyStudentInfo  v-if="showMenuNo === '3-2'"></ModifyStudentInfo>
      <ModifyCourseInfo   v-if="showMenuNo === '4-1'"></ModifyCourseInfo>
      <ModifyClassInfo    v-if="showMenuNo === '4-2'"></ModifyClassInfo>
      <el-footer></el-footer>
    </el-container>
  </el-container>
</template>

<script>
import Header from '@/components/Header'
import QueryTeachers from '@/components/QueryTeachers'
import QueryStudents from '@/components/QueryStudents'
import QueryCourses from '@/components/QueryCourses'
import QueryClasses from '../components/QueryClasses'
import InsertUser from '../components/InsertUser'
import UpdateDeleteUser from '../components/UpdateDeleteUser'
import QueryUsers from '../components/QueryUsers'
import ModifyTeacherInfo from '../components/ModifyTeacherInfo'
import ModifyStudentInfo from '../components/ModifyStudentInfo'
import ModifyCourseInfo from '../components/ModifyCourseInfo'
import ModifyClassInfo from '../components/ModifyClassInfo'

export default {
  name: 'manager',
  components: {
    ModifyClassInfo, ModifyCourseInfo, ModifyStudentInfo, ModifyTeacherInfo, QueryUsers, UpdateDeleteUser, InsertUser, QueryClasses, QueryCourses, QueryStudents, QueryTeachers, Header},
  data () {
    return {
      menuName: [
        { submenu: '信息查询', icon: 'el-icon-location', childs: ['账号信息查询', '教师信息查询', '学生信息查询', '课程信息查询', '课堂信息查询'] },
        { submenu: '账号信息管理', icon: 'el-icon-menu', childs: ['添加账号信息', '更新删除账号'] },
        { submenu: '个体信息管理', icon: 'el-icon-location', childs: ['教师信息管理', '学生信息管理'] },
        { submenu: '课程课堂管理', icon: 'el-icon-location', childs: ['课程信息管理', '课堂信息管理'] }
        // ,{ submenu: '任务成绩管理', icon: 'el-icon-location', childs: ['课堂任务管理', '成绩信息管理'] }
      ],
      usrname: '',
      showMenuNo: '0',
      isCollapse: true,
      menuList: [ 'Manager' ]
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
      this.menuList = ['Manager']
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
