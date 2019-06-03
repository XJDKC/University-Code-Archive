<template>
  <el-header style="text-align: right; font-size: 12px;">
    <ShowMenu v-on:menuIconClicked="collapseMenu"></ShowMenu>

    <Breadcrumb :newList="menuList" />

    <Dropdown v-on:quit="quit" v-on:help="help"></Dropdown>
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
    'newList': Array
  },
  data () {
    return {
      menuList: [ 'Student' ]
    }
  },
  methods: {
    collapseMenu (data) {
      this.$emit('collapseMenu', data)
    },
    help () {
      this.$emit('help')
    },
    quit () {
      this.$emit('quit')
    }
  },
  watch: {
    newList (list) {
      this.menuList = list
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
