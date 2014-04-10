import AIE
import game
import math
import Level_Grid

#Tank Entity
#   A simple entity that can be placed on the screen with a right click, you should modify this so that the tank can be told to 
#   navigate to a point instead of instantly move.

class TankEntity:

	def __init__(self, level):
		self.level = level
		self.Position = ( 600, 300 )
		self.Velocity = ( 0, 0 )
		self.Target = ( 600, 300 )
		self.Waypoint = None
		self.Rotation = 0
		self.spriteName = "./images/PlayerTanks.png"
		self.size = (57, 72 )
		self.origin = (0.5, 0.5)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1],
                                          71.0/459.0, 1.0 - 72.0/158.0, 128/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID
		level.register( self, TankEntity.recalculateRoute )
		self.turret = Turret(self)

	def recalculateRoute( self, level ):
		print "Recalculating route from position ", self.Position, " to target ", self.Target
		if( self.Position != self.Target and
            level.lineOfSight( self.Position[0], self.Position[1], self.Target[0], self.Target[1], True, True ) ):
			self.Waypoint = self.Target
		else:
			self.Waypoint = None

	def isWithin( self, xPos, yPos, radius ):
		if( xPos == self.Position[0] and yPos == self.Position[1] ):
			return True
		squaredDistance = ( self.Position[0] - xPos )**2 + ( self.Position[1] - yPos )**2
		if( squaredDistance < radius**2 ):
			return True
		return False

	def slowWithin( self, xPos, yPos, radius, breakPower ):
		if( xPos == self.Position[0] and yPos == self.Position[1] ):
			return ( -self.Velocity[0] * breakPower, -self.Velocity[1] * breakPower )
		if( not self.isWithin( xPos, yPos, radius ) ):
			return ( 0.0, 0.0 )
		squaredDistance = ( self.Position[0] - xPos )**2 + ( self.Position[1] - yPos )**2
		breakStrength = ( 1 - squaredDistance/radius**2 ) * breakPower
		return ( -self.Velocity[0] * breakStrength, -self.Velocity[1] * breakStrength )

	def seek( self, xPos, yPos, turnPower ):
		displacement = ( self.Position[0] - xPos, self.Position[1] - yPos )
		squaredDistance = displacement[0]**2 + displacement[1]**2
		if( squaredDistance <= 0.0 ):
			return ( 0.0, 0.0 )
		distance = math.sqrt( squaredDistance )
		speed = math.sqrt( self.Velocity[0]**2 + self.Velocity[1]**2 )
		return ( -turnPower * ( displacement[0]*speed/distance + self.Velocity[0] ),
                 -turnPower * ( displacement[1]*speed/distance + self.Velocity[1] ) )

	def accelerateTo( self, speed, acceleration, cruiseSpeedRange ):

        # if already at desired speed, no more acceleration is needed
		speedSquared = self.Velocity[0]**2 + self.Velocity[1]**2
		if( speedSquared == speed**2 ):
			return ( 0.0, 0.0 )

        # calculate acceleration direction
		currentSpeed = math.sqrt( speedSquared )
		direction = ( 0.0, 0.0 )
		if( currentSpeed <= 0.0 ):
			direction = ( math.cos( self.Rotation ), math.sin( self.Rotation ) )
		else:
			direction = ( self.Velocity[0] / currentSpeed,
                          self.Velocity[1] / currentSpeed )

        # calculate acceleration magnitude
		cruiseMinSpeed = speed - min( speed, cruiseSpeedRange )
		cruiseMaxSpeed = speed + cruiseSpeedRange
		magnitude = acceleration if ( currentSpeed < speed ) else -acceleration
		if( cruiseMinSpeed < currentSpeed < cruiseMaxSpeed ):
			speedThreshold = ( cruiseMinSpeed if ( currentSpeed < speed ) else cruiseMaxSpeed )
			magnitude *= ( currentSpeed - speed ) / ( speedThreshold - speed )

        # return result
		return ( direction[0] * magnitude, direction[1] * magnitude )

	def accelerateAndSeek( self, xPos, yPos, turnPower, speed, acceleration, cruiseSpeedRange ):
		seek = self.seek( xPos, yPos, turnPower )
		accel = self.accelerateTo( speed, acceleration, cruiseSpeedRange )
		return ( seek[0] + accel[0], seek[1] + accel[1] )

	def arriveWithin( self, xPos, yPos, breakRadius, breakPower, turnPower, speed, acceleration, cruiseSpeedRange ):
		if( self.isWithin( xPos, yPos, breakRadius ) ):
			seek = self.seek( xPos, yPos, turnPower )
			slow = self.slowWithin( xPos, yPos, breakRadius, breakPower )
			return ( seek[0] + slow[0], seek[1] + slow[1] )
		return self.accelerateAndSeek( xPos, yPos, turnPower, speed, acceleration, cruiseSpeedRange );

	def avoidCollisions( self, collisionDistance, turnDistance, turnPower, fDeltaTime ):

		# if inside an obstacle, it's far too late.  Just keep going.
		xGrid, yGrid = self.level.toGrid( self.Position[0], self.Position[1] )
		if( self.level.obstacleAt( xGrid, yGrid ) ):
			return ( 0.0, 0.0 )

        # check to see if there are any obstacles ahead given current velocity
		xDir = 0 if ( 0.0 == self.Velocity[0] ) else -1 if ( 0.0 > self.Velocity[0] ) else 1
		yDir = 0 if ( 0.0 == self.Velocity[1] ) else -1 if ( 0.0 > self.Velocity[1] ) else 1
		xObstacle = False if ( 0 == xDir ) else self.level.obstacleAt( xGrid + xDir, yGrid )
		yObstacle = False if ( 0 == yDir ) else self.level.obstacleAt( xGrid, yGrid + yDir )
		xyObstacle = ( False if ( 0 == xDir or 0 == yDir or ( xObstacle and yObstacle ) )
                             else self.level.obstacleAt( xGrid + xDir, yGrid + yDir ) )

        # if there are no obstacles in the way, just keep going
		if( not xObstacle and not yObstacle and not xyObstacle ):
			return ( 0.0, 0.0 )

		# "whiskers" should intersect with any obstacle edges close enough to worry about colliding
		speed = math.sqrt( self.Velocity[0]**2 + self.Velocity[1]**2 )
		direction = ( self.Velocity[0] / speed, self.Velocity[1] / speed )
		whiskerLength = collisionDistance + turnDistance + speed*reactionTime
		leftWhisker = ( self.Position[0] - direction[1]*collisionDistance,
                        self.Position[1] + direction[0]*collisionDistance )
		rightWhisker = ( self.Position[0] + direction[1]*collisionDistance,
                         self.Position[1] - direction[0]*collisionDistance )
		leftWhisker = ( leftWhisker[0], leftWhisker[1],
                        leftWhisker[0] + direction[0]*whiskerLength,
                        leftWhisker[1] + direction[1]*whiskerLength )
		rightWhisker = ( rightWhisker[0], rightWhisker[1],
                         rightWhisker[0] + direction[0]*whiskerLength,
                         rightWhisker[1] + direction[1]*whiskerLength )

        # the velocity if completely turned
		targetVelocity = ( 0.0, 0.0 )
        
        # distance
        
        # if the only obstacle is in the corner
		if( xyObstacle ):
			left = Geometry.SegmentSquareIntersect( leftWhisker[0], leftWhisker[1],
                                                    leftWhisker[2], leftWhisker[3],
                                                    xyCorners[0], xyCorners[1],
                                                    xyCorners[2], xyCorners[3] )
			right = Geometry.SegmentSquareIntersect( rightWhisker[0], rightWhisker[1],
                                                     rightWhisker[2], rightWhisker[3],
                                                     xyCorners[0], xyCorners[1],
                                                     xyCorners[2], xyCorners[3] )
			if( left and not right ):
				targetVelocity = ( 0.0, speed * yDir ) if ( 0.0 < direction[0]*direction[1] ) else ( speed * xDir, 0.0 )
			elif( right and not left ):
				targetVelocity = ( speed * xDir, 0.0 ) if ( 0.0 < direction[0]*direction[1] ) else ( 0.0, speed * yDir )
			elif( ( right and left ) or
                  Geometry.SegmentSquareIntersect( leftWhisker[2], leftWhisker[3],
                                                   rightWhisker[2], rightWhisker[3],
                                                   xyCorners[0], xyCorners[1],
                                                   xyCorners[2], xyCorners[3] ) ):
				corner = ( min( xyCorners[0], xyCorners[2] ) if xDir > 0 else max( xyCorners[0], xyCorners[2] ),
                           min( xyCorners[1], xyCorners[3] ) if yDir > 0 else max( xyCorners[1], xyCorners[3] ) )
				leftDistance = direction[0]*whiskerLength*( corner[0] - leftWhisker[0] ) +
                               direction[1]*whiskerLength*( corner[1] - leftWhisker[1] )
				rightDistance = direction[0]*whiskerLength*( corner[0] - rightWhisker[0] ) +
                               direction[1]*whiskerLength*( corner[1] - rightWhisker[1] )
                targetVelocity = ( speed * xDir, 0.0 ) if ( 0.0 < direction[0]*direction[1] ) else ( 0.0, speed * yDir )

        # check to see if obstacles are close enough to bother turning and, if so, which is closest
		xDistance, temp1, temp2, temp3 = self.level.tileBorder( xGrid, yGrid, xDir, 0 )
		temp1, yDistance, temp2, temp3 = self.level.tileBorder( xGrid, yGrid, 0, yDir )
        xDistance = math.fabs( self.Position[0] - xDistance )
        yDistance = math.fabs( self.Position[1] - yDistance )
		xObstacle = False if ( not xObstacle ) else ( xDistance < turnDistance )
		yObstacle = False if ( not yObstacle ) else ( yDistance < turnDistance )
		xyObstacle = ( False if ( not xyObstacle or xObstacle or yObstacle )
                             else ( xDistance < turnDistance and yDistance < turnDistance ) )

        # if there are no obstacles in the way, just keep going
		if( not xObstacle and not yObstacle and not xyObstacle ):
			return ( 0.0, 0.0 )

        # if there are obstacles in both the x and the y directions, pick the closest one
		if( xObstacle and yObstacle ):
			xObstacle = ( ( xDistance < yDistance ) if ( xDistance != yDistance )
                          else ( math.fabs( self.Velocity[0] ) > math.fabs( self.Velocity[1] ) ) )
			yObstacle = not xObstacle

        # velocity if course turned parallel to nearest obstacle edge
		speed = math.sqrt( self.Velocity[0]**2 + self.Velocity[1]**2 )
		turnedVelocity = ( 0.0, 0.0 )

        # zero or less means not close enough to turn, 1 or more means colliding
		urgency = 0

        # figure out where to turn if the nearest obstacle is in the x-direction
		if( xObstacle ):
			if( 0 == yDir ):
				if( self.level.obstacleAt( xGrid, yGrid - 1 ) ):
					yDir = 1 if ( not self.level.obstacleAt( xGrid, yGrid + 1 ) or
                                  yDistance >= float(self.level.tileHeight()) / 2 ) else -1
				elif( self.level.obstacleAt( xGrid, yGrid + 1 ) ):
					yDir = -1
				elif( self.level.obstacleAt( xGrid + xDir, yGrid - 1 ) ):
					yDir = 1 if ( not self.level.obstacleAt( xGrid + xDir, yGrid + 1 ) or
                                  yDistance >= float(self.level.tileHeight()) / 2 ) else -1
				else:
					yDir = -1 if ( self.level.obstacleAt( xGrid + xDir, yGrid + 1 ) or
                                   yDistance < float(self.level.tileHeight()) / 2 ) else 1
			turnedVelocity = ( 0.0, speed * yDir )
        
        # figure out where to turn if the nearest obstacle is in the y-direction
		elif( yObstacle ):
			if( 0 == xDir ):
				if( self.level.obstacleAt( xGrid - 1, yGrid ) ):
					xDir = 1 if ( not self.level.obstacleAt( xGrid + 1, yGrid ) or
                                  xDistance >= float(self.level.tileWidth()) / 2 ) else -1
				elif( self.level.obstacleAt( xGrid + 1, yGrid ) ):
					xDir = -1
				elif( self.level.obstacleAt( xGrid - 1, yGrid + yDir ) ):
					xDir = 1 if ( not self.level.obstacleAt( xGrid + 1, yGrid + yDir ) or
                                  xDistance >= float(self.level.tileWidth()) / 2 ) else -1
				else:
					xDir = -1 if ( self.level.obstacleAt( xGrid + 1, yGrid + yDir ) or
                                   xDistance < float(self.level.tileWidth()) / 2 ) else 1
			turnedVelocity = ( speed * xDir, 0.0 )

        # figure out where to turn if the nearest obstacle is in the x- and y-directions
		elif( xyObstacle ):
			velocityTangent = math.fabs( self.Velocity[1] / self.Velocity[0] )
			displacementTangent = math.fabs( yDistance / xDistance )
			if( ( velocityTangent > displacementTangent or
                  ( velocityTangent == displacementTangent and velocityTangent > 1 ) ) and
                ( xDistance > collisionDistance or yDistance <= collisionDistance ) ):
				turnedVelocity = ( 0.0, speed * yDir )
			else:
				turnedVelocity = ( speed * xDir, 0.0 )

        # if there are no obstacles close enough to collide with

		# TODO
		return ( 0.0, 0.0 )

	def update(self, fDeltaTime ):

        # recalculate route if right mouse button is clicked
		mouseX, mouseY = AIE.GetMouseLocation()
		if( AIE.GetMouseButton(1) ):
			self.Target = ( mouseX, mouseY )
			self.recalculateRoute( self.level )

        # calculate acceleration
		acceleration = None
		if( None == self.Waypoint ):
			acceleration = self.accelerateTo( 0, 200, 10 )
		else:
			acceleration = self.arriveWithin( self.Waypoint[0], self.Waypoint[1], 20, 20, 10, 250, 250, 10 )

        # calculate position, velocity, and rotation
		self.Position = ( self.Position[0] + self.Velocity[0]*fDeltaTime + acceleration[0]*fDeltaTime**2/2,
                          self.Position[1] + self.Velocity[1]*fDeltaTime + acceleration[1]*fDeltaTime**2/2 )
		self.Velocity = ( self.Velocity[0] + acceleration[0] * fDeltaTime,
                          self.Velocity[1] + acceleration[1] * fDeltaTime )
		if( self.Velocity[0] != 0.0 or self.Velocity[1] != 0.0 ):
			self.Rotation = math.atan2( -self.Velocity[1], self.Velocity[0] )

        # move OpenGL sprite and turret sprite
		AIE.PositionSprite( self.spriteID, math.degrees( self.Rotation - ( math.pi / 2 ) ), self.Position[0], self.Position[1] )
		self.turret.update(fDeltaTime)
	
	def draw(self):
		
		AIE.DrawSprite( self.spriteID )
		self.turret.draw()
		
	def getImageName(self):
		return self.imageName
		
	def getState(self):
		return self.state
	
	def getSpriteID(self):
		return self.spriteID
		
	def setSpriteID(self, a_spriteID):
		self.spriteID = a_spriteID
	
	def getPosition(self):
		return self.Position

	def cleanUp(self):
		self.turret.cleanUp()
		AIE.DestroySprite( self.spriteID )
		
#Turret
#    This is an Entity Object that has an owner, it is up to you to implement inheritance (BaseEntity->Turret) 
#    The Turret's position is based on the location of it's owner, if it's owner (in this scenario a Tank) is moveable
#    The turret will move with it's base/owner

class Turret:
	
	def __init__(self, owner):
		self.owner = owner
		self.Position = ( 0, 0 )
		self.Rotation = 0
		self.spriteName = "./images/PlayerTanks.png"
		self.size = (29, 60 )
		self.origin = (0.55, 0.75)
		self.spriteID = AIE.CreateSprite( self.spriteName, self.size[0], self.size[1], self.origin[0], self.origin[1],
                                          129.0/459.0, 1.0 - 61.0/158.0, 157.0/459.0, 1.0 , 0xff, 0xff, 0xff, 0xff )
		print "spriteID", self.spriteID
	
	def update(self, fDeltaTime):
		turretLocation = self.owner.getPosition()
		mouseX, mouseY = AIE.GetMouseLocation()
		rotation = math.atan2( -mouseY + turretLocation[1], mouseX - turretLocation[0] )
		AIE.PositionSprite( self.spriteID, math.degrees( rotation - ( math.pi / 2 ) ), turretLocation[0], turretLocation[1] )
		
	def draw(self):
		AIE.DrawSprite( self.spriteID )
	
	def	cleanUp(self):
		AIE.DestroySprite( self.spriteID )
		