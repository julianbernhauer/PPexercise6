// original code
function uploadFilesOld(files, callback) {
  let uploaded = 0;
  let results = [];

  for (let file of files) {
    uploadFile(file, (response) => {
      results.push(response);
      uploaded++;

      if (uploaded === files.length) {
        callback(results);
      }
    });
  }
}

// Helper functions
function uploadFile(file) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (file === "file2.jpg") {
        reject(`Failed to upload ${file}`);
      } else {
        resolve(`File ${file} uploaded`);
      }
    }, 1000);
  });
}


// new implementation using promises
function uploadFiles(files) {
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      if (!files || files.length === 0) {
        reject(new Error("You should provide files"));
      } else {
        resolve(`YOu successfully uploaded your ${files.length} files`);
      }
    }, 2000);
  });
}

// Test case 1
const files1 = ["file1.txt", "file3.pdf"];
uploadFiles(files1)
  .then((results) => {
    console.log("All files uploaded:");
    console.log(results);
  })
  .catch((error) => {
    console.error("Error occurred:", error);
  });

/* Expected Output:
All files uploaded:
[ 'File file1.txt uploaded', 'File file3.pdf uploaded' ]
*/

// Test case 2: Simulate error
const files2 = ["file1.txt", "file2.jpg", "file3.pdf"];
uploadFiles(files2)
  .then((results) => {
    console.log("All files uploaded:");
    console.log(results);
  })
  .catch((error) => {
    console.error("Error occurred:", error);
  });

/* Expected Output:
Error occurred: Failed to upload file2.jpg
*/


