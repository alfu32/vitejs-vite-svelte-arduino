<script>

	import { createEventDispatcher } from 'svelte';

const dispatch = createEventDispatcher();

  function sayHello() {
    dispatch('message', {
      text: 'Hello!'
    });
  }
  export let id = "0"
  export let name = "D0"
  export let currentValue = 50
  export let nextValue = 50
  const setPwmValue = (e) => {
    nextValue = parseInt(e.target.value)
  }
  const sendPwmValue = (e) => {
    nextValue = parseInt(e.target.value)
    if(currentValue!=nextValue){
      dispatch('pinValueChanged', {
        id,
        name,
        nextValue,
        currentValue,
      });
    }
  }
</script>

<div class="PwmOut">
  <h4 style="display:inline-block">PWM[{id}]({name})</h4>
  <input
    type="range"
    min="0"
    max="100"
    step="10"
    value={currentValue}
    on:mousemove={e=>setPwmValue(e)}
    on:mouseup={e=>sendPwmValue(e)}
  />

  <pre class="num-display">{currentValue.toFixed(0).padStart(4,' ')}%</pre>
</div>

<style>
.num-display {
  min-width: 5em;
  max-width: 5em;
  display: inline-block;
}
</style>