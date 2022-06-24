<script>

  export let id = D0
  export let pinValue = 50
  const setPwmValue = (e) => {
    pinValue = e.target.value
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

  <span style="display: inline-block;min-width: 3rem;max-width:3rem;text-align:right">{pinValue}%</span>
</div>