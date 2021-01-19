import Vue from 'vue'
import Router from 'vue-router'
// import HelloWorld from '@/components/HelloWorld'
import Header from '@/components/Header'
import login from '@/pages/login'
import manager from '@/pages/manager'
import teacher from '@/pages/teacher'
import student from '@/pages/student'

Vue.use(Router)

export default new Router({
  routes: [
    // {
    //   path: '/',
    //   name: 'HelloWorld',
    //   component: HelloWorld
    // },
    {
      path: '/index',
      name: 'Header',
      component: Header
    },
    {
      path: '/login',
      alias: '/',
      name: 'login',
      component: login
    },
    {
      path: '/manager/:Usrname',
      name: 'manager',
      component: manager
    },
    {
      path: '/teacher/:Usrname',
      name: 'teacher',
      component: teacher
    },
    {
      path: '/student/:Usrname',
      name: 'student',
      component: student
    }
  ]
})
