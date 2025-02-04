// original code
function authenticateUserOld(credentials, callback) {
  validateCredentials(credentials, (isValid) => {
    if (isValid) {
      getUserDetails(credentials.username, (userDetails) => {
        getUserPermissions(userDetails, (permissions) => {
          callback({ userDetails, permissions });
        });
      });
    } else {
      callback(null);
    }
  });
}

// Helper functions
function validateCredentials(credentials) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(credentials.password === "password123");
    }, 500);
  });
}

function getUserDetails(username) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve({ id: 1, name: "John Doe", username });
    }, 500);
  });
}

function getUserPermissions(user) {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(["read", "write"]);
    }, 500);
  });
}

// new implementation using async/await
async function authenticateUser(credentials) {
  // TODO: add necessary code here
  return { userDetails, permissions };
}


// Test case 1: Valid credentials
const validCredentials = { username: "johndoe", password: "password123" };
authenticateUser(validCredentials)
  .then((result) => {
    if (result) {
      console.log("User authenticated successfully:", result);
    } else {
      console.log("Authentication failed.");
    }
  })
  .catch((error) => {
    console.error("Error occurred:", error);
  });

/* Expected Output:
User authenticated successfully: {
  userDetails: { id: 1, name: 'John Doe', username: 'johndoe' },
  permissions: [ 'read', 'write' ]
}
*/

// Test case 2: Invalid credentials
const invalidCredentials = { username: "johndoe", password: "wrongpassword" };
authenticateUser(invalidCredentials)
  .then((result) => {
    if (result) {
      console.log("User authenticated successfully:", result);
    } else {
      console.log("Authentication failed.");
    }
  })
  .catch((error) => {
    console.error("Error occurred:", error);
  });

/* Expected Output:
Authentication failed.
*/

