<template>
  <el-header style="text-align: right; font-size: 12px;">
    <ShowMenu v-on:menuIconClicked="collapseMenu"></ShowMenu>

    <Breadcrumb :menuList="menuList" />

    <Dropdown :usrname="usrname" v-on:quit="quit"></Dropdown>
  </el-header>
</template>

<script>
import ShowMenu from '@/components/ShowMenu'
import Breadcrumb from '@/components/Breadcrumb'
import Dropdown from '@/components/Dropdown'

export default {
  name: 'Header',
  components: {Dropdown, Breadcrumb, ShowMenu},
  props: {
    usrname: '',
    menuList: Array
  },
  methods: {
    collapseMenu (data) {
      this.$emit('collapseMenu', data)
    },
    quit () {
      console.log(1)
      this.$emit('quit')
    }
  },
  watch: {
    menuList (para) {
      this.menuList = para
    }
  }
}
</script>

<style scoped>
  .el-header {
    text-align: center;
    height: 50px;
    overflow: hidden;
    position: relative;
    background: #fff;
    -webkit-box-shadow: 0 1px 4px rgba(0,21,41,.08);
    box-shadow: 0 1px 4px rgba(0,21,41,.08);
  }
</style>
