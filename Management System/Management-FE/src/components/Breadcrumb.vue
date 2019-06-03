<template>
  <el-breadcrumb class="app-breadcrumb" separator-class="el-icon-arrow-right">
    <transition-group name="breadcrumb">
      <el-breadcrumb-item v-for="item in menuList" v-bind:key="item">
        <a>{{ item }}</a>
      </el-breadcrumb-item>
    </transition-group>
  </el-breadcrumb>
</template>

<script>

export default {
  name: 'Breadcrumb',
  props: {
    'newList': Array
  },
  data () {
    return {
      menuList: this.newList
    }
  },
  watch: {
    newList (newList) {
      // console.log(newList)
      this.menuList = newList
    }
  }
}
</script>

<style lang="scss" scoped>
  .app-breadcrumb.el-breadcrumb {
    float: left;
    margin-top: 5px;
    display: inline-block;
    font-size: 14px;
    line-height: 50px;
    margin-left: 8px;
    .no-redirect {
      color: #97a8be;
      cursor: text;
    }
  }
</style>
