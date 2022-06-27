<script>
  import PinController from "./lib/PinController.svelte";
  import AnalogInput from "./lib/AnalogInput.svelte";
  import DigitalInput from "./lib/DigitalInput.svelte";
  import { onMount } from 'svelte';

  let debounceId=0
  function newUiPinValue(e) {
    clearTimeout(debounceId);
    debounceId = setTimeout(async () =>{
      const {id,name,nextValue} = (e.detail);
      console.log(e.detail);
      const r = await fetch(`/pin?pinIdx=${id}&val=${nextValue}`)
      let result = {...currentState}
      try{
        result = await r.json()
      }catch(err){
        console.log(err)
        result.pins[id].pwm=nextValue
      }
      currentState = {...result};
    },400)
  }
  async function synchro() {
    const r = await fetch(`/pins`)
    let result = {...currentState}
    let text=""
    try{
      text = await r.text()
      result = JSON.parse(text)
    }catch(err){
      console.log(err.message);
      console.log(text);
    }
    return result;
  }
  let currentState = {
    host: "mini-michi",
    ultrasonicDistance: 371709,
    pinA0Voltage: 0.25,
    pins: [
      { name: "D0", pinId: 16, pwm: 10, actualValue: 25 },
      { name: "D1", pinId: 5, pwm: 20, actualValue: 51 },
      { name: "D2", pinId: 4, pwm: 30, actualValue: 76 },
      { name: "D3", pinId: 0, pwm: 40, actualValue: 102 },
      { name: "D4", pinId: 2, pwm: 5, actualValue: 12 },
      { name: "D5", pinId: 14, pwm: 60, actualValue: 153 },
      { name: "D6", pinId: 12, pwm: 70, actualValue: 178 },
      { name: "D7", pinId: 13, pwm: 80, actualValue: 204 },
      { name: "D8", pinId: 15, pwm: 90, actualValue: 229 },
    ],
  };

  onMount(() => {
    
      ///// let intvId = setInterval(async() => {
      /////   const result = await synchro()
      /////   currentState = result;
      ///// 
      ///// }, 2000);
      ///// 
      ///// return () => clearInterval(intvId);
  });
</script>

<main>
  <PinController id="9" name="A0" pinType="in" currentValue={currentState.pinA0Voltage}/>
  <PinController id="0" name="D0" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D0').pwm}/>
  <PinController id="1" name="D1" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D1').pwm}/>
  <PinController id="2" name="D2" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D2').pwm}/>
  <PinController id="3" name="D3" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D3').pwm}/>
  <PinController id="4" name="D4" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D4').pwm}/>
  <PinController id="5" name="D5" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D5').pwm}/>
  <PinController id="6" name="D6" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D6').pwm}/>
  <PinController id="7" name="D7" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D7').pwm}/>
  <PinController id="8" name="D8" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D8').pwm}/>
  <PinController id="8" name="D8" pinType="out" on:pinValueChanged={newUiPinValue} currentValue={currentState.pins.find(v => v.name=='D8').pwm}/>
</main>

<style>
</style>
