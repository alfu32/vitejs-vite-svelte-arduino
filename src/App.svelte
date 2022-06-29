<script>
  import PinController from "./lib/PinController.svelte";
  import AnalogInput from "./lib/AnalogInput.svelte";
  import DigitalInput from "./lib/DigitalInput.svelte";
  import { onMount } from 'svelte';


  async function fetchResult(httpResponse){
    let result=null
    let text=""
    try{
        text = await httpResponse.text()
        result = JSON.parse(text)
        return result;
      }catch(err){
        console.log(err)
        return null
      }
  }

  let debounceId=0;

  async function newUiPinValue(e) {
    const {id,name,nextValue} = (e.detail);
    console.log(e.detail);
    return new Promise((resolve,reject)=>{
      clearTimeout(debounceId);
      debounceId = setTimeout(async () =>{
        const httpResponse = await fetch(`/pin?pinIdx=${id}&val=${nextValue}`)
        currentState = fetchResult(httpResponse)||currentState;
        resolve(currentState);
      },400);
    });
  }

  async function synchro() {
    const httpResponse = await fetch(`/pins`)
    currentState=fetchResult(httpResponse)||currentState;
    return currentState;
  }
  let currentState = null;
  function mockSynchro(){
    return new Promise((resolve,reject)=>{
      setTimeout(()=>{
        currentState=({
          host: "mini-michi",
          platform: "fake",
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
            { name: "T0", pinId: 10, pwm: 90, actualValue: 229 },
            { name: "T1", pinId: 11, pwm: 91, actualValue: 229 },
            { name: "T2", pinId: 12, pwm: 92, actualValue: 229 },
            { name: "T3", pinId: 13, pwm: 93, actualValue: 229 },
          ],
        })
        resolve(currentState);
      },1000)
    });
  }

  onMount(async () => {
    
      ///// let intvId = setInterval(async() => {
      await mockSynchro()
      ///// 
      ///// }, 2000);
      ///// 
      ///// return () => clearInterval(intvId);
  });
</script>

<main>
  {#if currentState!=null}
    <PinController id="9" name="A0" pinType="in" currentValue={currentState.pinA0Voltage}/>
    {#each currentState.pins as pin}
      <PinController id={pin.id} name={pin.name} pinType="out" on:pinValueChanged={newUiPinValue} currentValue={pin.pwm}/>
    {/each}
  {/if}
</main>

<style>
</style>
