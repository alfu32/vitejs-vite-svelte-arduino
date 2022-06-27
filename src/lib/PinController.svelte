<script>

	import { createEventDispatcher } from 'svelte';

const dispatch = createEventDispatcher();

  export let id = "0"
  export let name = "D0"
  export let currentValue = 50
  let nextValue = 50
  export let pinType = "out"
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
{#if pinType=='out'}
<div class="PwmOut">
  <h4 style="display:inline-block">PWM[{id}]({name})</h4>
  <input
    type="range"
    min="0"
    max="100"
    step="5"
    value={currentValue}
    on:change={e=>sendPwmValue(e)}
    on:mousemove={e=>setPwmValue(e)}
    on:touchmove={e=>setPwmValue(e)}
    on:pointermove={e=>setPwmValue(e)}
    on:mouseup={e=>sendPwmValue(e)}
    on:pointerup={e=>sendPwmValue(e)}
    style="width:70%"
  />

  <pre class="num-display">{currentValue.toFixed(0).padStart(4,' ')}%</pre>
  <pre class="num-display">{nextValue.toFixed(0).padStart(4,' ')}%</pre>
</div>
{:else if pinType=='in'}
<div class="DigitalInput">
  <h4 style="display:inline-block">DigitalInput({id})</h4>
  <pre class="num-display">{currentValue}</pre>
  <br/>
</div>
{:else}
<div>{pinType} pinType is undefined</div>
{/if}
<style>
.num-display {
  min-width: 5em;
  max-width: 5em;
  display: inline-block;
}
</style>