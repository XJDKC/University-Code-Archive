// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import axios from 'axios'
import VueAxios from 'vue-axios'
import ElementUI from 'element-ui'
// import '@/styles/element-theme/index.css'

import './styles/index.scss'

import App from './App'
import router from './router'

Vue.config.productionTip = false
Vue.config.debug = true

Vue.use(VueAxios, axios)
Vue.use(ElementUI)

/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  components: { App },
  template: '<App/>'
})
