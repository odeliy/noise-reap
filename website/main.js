const expandList = document.getElementById('expandList')
const moduleList = document.querySelector('.module-list')
let listOpen = false

expandList.addEventListener('click', () => {
  if (listOpen === false) {
    listOpen = true
    moduleList.classList.remove('hide')
    expandList.innerText = '(hide)'
  } else {
    listOpen = false
    moduleList.classList.add('hide')
    expandList.innerText = '(show)'
  }
})
