<script>
  import './AnalogInput.css'
  export let id = "D5"
  let reading = 0.3
  let buffer=""
  let intvId = setInterval(
    ()=>{
      
      reading=Math.random()>0.5?1:0
      const chr = (reading?'⎻':'＿')
      let newBuffer=buffer+(buffer[buffer.length-1]==chr?(chr+chr):reading?'/'+chr:'\\'+chr)
      if(newBuffer.length>16){
        newBuffer = newBuffer.substring(1)
      }
      buffer = newBuffer
      
    },500
  )
</script>

<div class="DigitalInput">
  <h4 style="display:inline-block">DigitalInput({id})</h4>
  <pre class="num-display">{buffer}</pre>
  <br/>
</div>