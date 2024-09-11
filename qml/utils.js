.pragma library


function cutPathEnd(path) {
    if (typeof path !== 'string' ||
            path.split('/').length < 2) {
        return ""
    }

    let words = path.split('/')
    return words[words.length - 1]
}

function cutOffPathEnd(path) {
    if (typeof path !== 'string' ||
            path.split('/').length < 2 ||
            path.split('/')[1] === "") {
        return ""
    }

    return path.slice(0, path.lastIndexOf('/') + 1)
}

function convertBytesToGigabytes(bytes) {
    return Math.trunc(bytes / (1024 * 1024 * 1024.0))
}

function convertBytesToString(bytes) {
    let bytesArray = String(bytes).split("").reverse()
    let newBytesArray = bytesArray

    for (let index = 0 + 3, iteration = 0;
            index < bytesArray.length;
            index += 3, ++iteration) {
        newBytesArray.splice(index + iteration, 0, " ")
    }

    let bytesString = newBytesArray.reverse().join('')
    return bytesString.trim()
}

function convertBytesToShortString(bytes)
{
    if (bytes === 0) {
        return "";
    }

    if (bytes < 1024) {
        return String(bytes) + " bytes";
    }
    else if (bytes < (1024 * 1024)) {
        return (bytes / 1024.0).toFixed(1) + " KB";
    }
    else if (bytes < (1024 * 1024 * 1024)) {
        return (bytes / (1024 * 1024.0)).toFixed(1) + " MB";
    }
    else if (bytes < (1024 * 1024 * 1024 * 1024)) {
        return (bytes / (1024 * 1024 * 1024.0)).toFixed(1) + " GB";
    }
    else {
        console.log("Can't convert so many bytes..." + bytes)
        return ""
    }
}
