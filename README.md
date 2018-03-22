
# react-native-payfubao

## Getting started

`$ npm install react-native-payfubao --save`

### Mostly automatic installation

`$ react-native link react-native-payfubao`

### Manual installation


#### iOS

1. In XCode, in the project navigator, right click `Libraries` ➜ `Add Files to [your project's name]`
2. Go to `node_modules` ➜ `react-native-payfubao` and add `RNPayfubao.xcodeproj`
3. In XCode, in the project navigator, select your project. Add `libRNPayfubao.a` to your project's `Build Phases` ➜ `Link Binary With Libraries`
4. Run your project (`Cmd+R`)<

#### Android

1. Open up `android/app/src/main/java/[...]/MainActivity.java`
  - Add `import com.reactlibrary.RNPayfubaoPackage;` to the imports at the top of the file
  - Add `new RNPayfubaoPackage()` to the list returned by the `getPackages()` method
2. Append the following lines to `android/settings.gradle`:
  	```
  	include ':react-native-payfubao'
  	project(':react-native-payfubao').projectDir = new File(rootProject.projectDir, 	'../node_modules/react-native-payfubao/android')
  	```
3. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
  	```
      compile project(':react-native-payfubao')
  	```

## Usage
```javascript
import RNPayfubao from 'react-native-payfubao';

// TODO: What to do with the module?
RNPayfubao;
```
