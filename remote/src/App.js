import React from 'react';
import request from 'request';

import './App.css';

import Home from './components/Home/Home.jsx';

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      doorStatus: 'Close',
    };
    this.openDoor = this.openDoor.bind(this);
    this.closeDoor = this.closeDoor.bind(this);
  }

  componentDidMount() {
    const options = { method: 'GET',
      url: 'http://172.20.10.8/',
      headers: {
        'Cache-Control': 'no-cache',
      },
    };

    request(options, (error, response, body) => {
      const lineStatus = body.match(/[^\r\n]+/g)[7];
      this.setState({
        doorStatus: lineStatus,
      });
    });
  }

  openDoor() {
    const options = { method: 'GET',
      url: 'http://172.20.10.8/door/open',
      headers: {
        'Cache-Control': 'no-cache',
      },
    };

    request(options, (error, response, body) => {
      const lineStatus = body.match(/[^\r\n]+/g)[7];
      this.setState({
        doorStatus: lineStatus,
      });
    });
  }

  closeDoor() {
    const options = { method: 'GET',
      url: 'http://172.20.10.8/door/close',
      headers: {
        'Cache-Control': 'no-cache',
      },
    };

    request(options, (error, response, body) => {
      const lineStatus = body.match(/[^\r\n]+/g)[7];
      this.setState({
        doorStatus: lineStatus,
      });
    });
  }

  render() {
    return (
      <div className="App">
        <Home
          doorStatus={this.state.doorStatus}
          openDoor={this.openDoor}
          closeDoor={this.closeDoor}
        />
      </div>
    );
  }
}

export default App;
