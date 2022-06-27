<script>
  import {human,randomSeries} from '../physical.js'
  export let name = "D0"
  export let reading = 1.67
  /// let intvId = setInterval(
  ///   ()=>{
  ///     reading=randomSeries({ min: 0, max: 3.3, granularity: 0.1 })
  ///   },1000
  /// )

</script>

<div class="AnalogInput">
  <h4 style="display:inline-block">AnalogIn({name})</h4>
  <input
    type="range"
    min="0"
    max="3300"
    step="10"
    value={reading*1000}
    readonly={true}
  />
  <pre class="num-display">{human({ value: reading, unit: 'V' })}</pre>
  <pre class="num-display">{(reading/3.3*100).toFixed(3)}%</pre>
  <br/>
</div>
<style>
.num-display {
  min-width: 5em;
  max-width: 5em;
  display: inline-block;
}
</style>