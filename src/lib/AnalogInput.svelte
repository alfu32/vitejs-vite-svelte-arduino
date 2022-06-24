<script>
  import {human,randomSeries} from '../physical.js'
  export let id = "D0"
  let reading = 1.67
  let intvId = setInterval(
    ()=>{
      reading=randomSeries(randomSeries({ min: 0, max: 3.3, granularity: 0.001 }))
    },1000
  )

</script>

<div class="AnalogInput">
  <h4 style="display:inline-block">AnalogIn({id})</h4>
  <input
    type="range"
    min="-100"
    max="100"
    step="10"
    value={reading}
  />
  <pre style="min-width:10em;max-width:10em;display:inline-block">{human({ value: reading, unit: 'V' })}</pre>
  <br/>{reading.toFixed(6)}

  <span style="display: inline-block;min-width: 3rem;max-width:3rem;text-align:right">{reading}%</span>
</div>