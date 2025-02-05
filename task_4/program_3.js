// Original code
function getWeatherOld(city, callback) {
  fetchWeather(city, (response) => {
    parseWeather(response, (data) => {
      callback(data);
    });
  });
}

// Helper functions
function fetchWeather(city) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (city === "Unknown City") {
        reject("City not found");
      } else {
        resolve({ city, temperature: 25, condition: "Sunny" });
      }
    }, 1000);
  });
}

function parseWeather(response) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(`${response.city}: ${response.temperature}°C, ${response.condition}`);
    }, 500);
  });
}


// new implementation using promises
function getWeather(city) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (city === "Unknown City") {
        reject("City not found");
      } else {
        resolve({ city, temperature: 25, condition: "Sunny" });
      }
    }, 1000);
  });
}

// Test case 1: Fetch weather for a valid city
getWeather("New York")
  .then((result) => {
    console.log("Weather data:", result);
  })
  .catch((error) => {
    console.error("Error occurred:", error);
  });

/* Expected Output:
Weather data: New York: 25°C, Sunny
*/

// Test case 2: Simulate error
getWeather("Unknown City")
  .then((result) => {
    console.log("Weather data:", result);
  })
  .catch((error) => {
    console.error("Error occurred:", error);
  });

/* Expected Output:
Error occurred: City not found
*/

