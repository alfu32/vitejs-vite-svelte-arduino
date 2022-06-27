<script>
  import PwmController from "./lib/PwmController.svelte";
  import AnalogInput from "./lib/AnalogInput.svelte";
  import DigitalInput from "./lib/DigitalInput.svelte";
  import { onMount } from 'svelte';
  async function newUiPinValue(e) {
    const {id,name,nextValue} = (e.detail);
    console.log(e.detail);
    const r = await fetch(`/pin?pinIdx=${id}&val=${nextValue}`)
    const result = await r.json()
    currentState = result;
  }
  let currentState = {
    host: "mini-michi",
    ultrasonicDistance: 371709,
    pinA0Voltage: 0,
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
    
    let intvId = setInterval(async() => {
      // eading = randomSeries({ min: 0, max: 3.3, granularity: 0.1 });
    const r = await fetch("/pin?pinIdx=4&val=5z")
    const result = await r.json()
    currentState = result;
    //// const r = await fetch("http://192.168.1.42/pin?pinIdx=4&val=5z", {
    ////   "headers": {
    ////     "accept": "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9",
    ////     "accept-language": "en-GB,en-US;q=0.9,en;q=0.8,de;q=0.7,ru;q=0.6,fr;q=0.5",
    ////     "cache-control": "max-age=0",
    ////     "upgrade-insecure-requests": "1"
    ////   },
    ////   "referrerPolicy": "strict-origin-when-cross-origin",
    ////   "body": null,
    ////   "method": "GET",
    ////   "mode": "cors",
    ////   "credentials": "omit"
    //// });

    }, 2000);

    return () => clearInterval(intvId);
  });
</script>

<main>
  <AnalogInput name="A0" />
  <PwmController id="0" name="D0" on:pinValueChanged={newUiPinValue} />
  <PwmController id="1" name="D1" on:pinValueChanged={newUiPinValue} />
  <PwmController id="2" name="D2" on:pinValueChanged={newUiPinValue} />
  <PwmController id="3" name="D3" on:pinValueChanged={newUiPinValue} />
  <PwmController id="4" name="D4" on:pinValueChanged={newUiPinValue} />
  <PwmController id="5" name="D5" on:pinValueChanged={newUiPinValue} />
  <PwmController id="6" name="D6" on:pinValueChanged={newUiPinValue} />
  <PwmController id="7" name="D7" on:pinValueChanged={newUiPinValue} />
  <PwmController id="8" name="D8" on:pinValueChanged={newUiPinValue} />
  <DigitalInput id="V0" />
  <DigitalInput id="V1" />
  <DigitalInput id="V2" />
</main>

<style>
</style>
