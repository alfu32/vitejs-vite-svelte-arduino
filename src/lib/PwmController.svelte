<script>
  import './AnalogInput.css'
  export let id = "D0"
  export let pinValue = 50
  const setPwmValue = (e) => {
    pinValue = parseInt(e.target.value)
  }
</script>

<div class="PwmOut">
  <h4 style="display:inline-block">PWM({id})</h4>
  <input
    type="range"
    min="-100"
    max="100"
    step="10"
    value={pinValue}
    on:mousemove={e=>setPwmValue(e)}
  />

  <pre class="num-display">{pinValue.toFixed(0).padStart(4,' ')}%</pre>
</div>