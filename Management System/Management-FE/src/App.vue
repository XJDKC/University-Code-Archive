<template>
  <transition>
    <router-view/>
  </transition>
</template>

<script>
export default {
  name: 'App'
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
html{
  height: 100%;
  margin: 0 auto;
}
body{
  height: 100%;
  margin: 0 auto;
}
</style>
